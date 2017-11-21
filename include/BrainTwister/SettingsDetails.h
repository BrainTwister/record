#pragma once

#include <boost/property_tree/ptree.hpp>
#include <fstream>
#include <memory>
#include <type_traits>
#include <vector>

namespace BrainTwister {
namespace SettingsDetails {

template <class T>
struct is_setting
{
  private:
    typedef char no;
    struct yes { no m[2]; };

    static T* make();
    template<typename U>
    static yes check(U*, typename U::is_setting* = 0);
    static no check(...);

  public:
    static bool const value = sizeof(check(make())) == sizeof(yes);
};

template <class T>
struct is_base_setting
{
  private:
    typedef char no;
    struct yes { no m[2]; };

    static T* make();
    template<typename U>
    static yes check(U*, typename U::is_base_setting* = 0);
    static no check(...);

  public:
    static bool const value = sizeof(check(make())) == sizeof(yes);
};

template <class Base>
struct PolymorphicLoader
{
    std::shared_ptr<Base> operator () (boost::property_tree::ptree const& pt) const;
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

/// Specialization for nested settings
template <class T>
struct GenericLoader<T, typename std::enable_if<is_setting<T>::value>::type>
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
struct GenericLoader<std::shared_ptr<T>, typename std::enable_if<!is_base_setting<T>::value>::type>
{
    std::shared_ptr<T> operator () (boost::property_tree::ptree const& pt, std::string const& key, std::shared_ptr<T> def) const
    {
        if (pt.count(key) == 0) return def;
        else if (pt.count(key) > 1) throw std::runtime_error("More than one key found for " + key + ".");

        return std::shared_ptr<T>(new T(pt.get<T>(key)));
    }

    std::shared_ptr<T> operator () (boost::property_tree::ptree const& pt) const
    {
        if (pt.size() != 1) throw std::runtime_error("More or less than one child for implicit tree node.");

        return std::shared_ptr<T>(new T(pt.get_value<T>()));
    }
};

template <class T>
struct GenericLoader<std::shared_ptr<T>, typename std::enable_if<is_base_setting<T>::value>::type>
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

} // namespace SettingsDetails
} // namespace BrainTwister
