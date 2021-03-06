#pragma once

#include <boost/property_tree/ptree.hpp>
#include <fstream>
#include <memory>
#include <type_traits>
#include <list>
#include <vector>

namespace BrainTwister {
namespace RecordDetails {

template <class T>
struct is_record
{
  private:
    typedef char no;
    struct yes { no m[2]; };

    static T* make();
    template <typename U>
    static yes check(U*, typename U::is_record* = 0);
    static no check(...);

  public:
    static bool const value = sizeof(check(make())) == sizeof(yes);
};

template <class T>
struct is_record_base
{
  private:
    typedef char no;
    struct yes { no m[2]; };

    static T* make();
    template <typename U>
    static yes check(U*, typename U::is_record_base* = 0);
    static no check(...);

  public:
    static bool const value = sizeof(check(make())) == sizeof(yes);
};

/// Primary template for fundamental types
template <class T, class Enable = void>
struct GenericLoader
{
    T operator () (boost::property_tree::ptree const& pt, std::string const& key, T def) const
    {
        return pt.get<T>(key, def);
    }

    T operator () (boost::property_tree::ptree const& pt) const
    {
        return pt.get_value<T>();
    }
};

/// Specialization for nested record
template <class T>
struct GenericLoader<T, typename std::enable_if<is_record<T>::value>::type>
{
    T operator () (boost::property_tree::ptree const& pt, std::string const& key, T def) const
    {
        if (pt.count(key) == 0) return def;
        return T(pt.get_child(key));
    }

    T operator () (boost::property_tree::ptree const& pt) const
    {
        return T(pt);
    }
};

template <class T>
struct GenericLoader<std::vector<T>>
{
    std::vector<T> operator () (boost::property_tree::ptree const& pt, std::string const& key, std::vector<T> def) const
    {
        if (pt.count(key) == 0) return def;
        std::vector<T> r;
        for (auto const& item : pt.get_child(key)) r.push_back(GenericLoader<T>()(item.second));
        return r;
    }
};

template <class T>
struct GenericLoader<std::list<T>>
{
    std::list<T> operator () (boost::property_tree::ptree const& pt, std::string const& key, std::list<T> def) const
    {
        if (pt.count(key) == 0) return def;
        std::list<T> r;
        for (auto const& item : pt.get_child(key)) r.push_back(GenericLoader<T>()(item.second));
        return r;
    }
};

template <class T>
struct GenericLoader<std::shared_ptr<T>, typename std::enable_if<!is_record_base<T>::value>::type>
{
    std::shared_ptr<T> operator () (boost::property_tree::ptree const& pt, std::string const& key, std::shared_ptr<T> def) const
    {
        if (pt.count(key) == 0) return def;
        else if (pt.count(key) > 1) throw std::runtime_error("More than one key found for " + key + ".");

        return std::make_shared<T>(pt.get<T>(key));
    }

    std::shared_ptr<T> operator () (boost::property_tree::ptree const& pt) const
    {
        if (pt.size() != 1) throw std::runtime_error("More or less than one child for implicit tree node.");

        return std::make_shared<T>(pt.get_value<T>());
    }
};

/// Load polymorphic structures
/// Specializations are in Register.h
template <class Base>
struct PolymorphicLoader
{
    std::shared_ptr<Base> operator () (boost::property_tree::ptree const& pt) const;
};

template <class T>
struct GenericLoader<std::shared_ptr<T>, typename std::enable_if<is_record_base<T>::value>::type>
{
    std::shared_ptr<T> operator () (boost::property_tree::ptree const& pt, std::string const& key, std::shared_ptr<T> def) const
    {
        if (pt.count(key) == 0) return def;
        else if (pt.count(key) > 1) throw std::runtime_error("More than one key found for " + key + ".");

        boost::property_tree::ptree child = pt.get_child(key);
        if (child.size() != 1) throw std::runtime_error("More or less than one child found for pointer (key = " + key + ").");
        return PolymorphicLoader<T>()(child);
    }

    std::shared_ptr<T> operator () (boost::property_tree::ptree const& pt) const
    {
        if (pt.size() != 1) throw std::runtime_error("More or less than one child for implicit tree node.");

        return PolymorphicLoader<T>()(pt);
    }
};

} // namespace RecordDetails
} // namespace BrainTwister
