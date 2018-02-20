BrainTwister Record
===================

BrainTwister record provides a linear, direct-accessible, heterogeneous
data structure. A record will be defined with a single macro

```
BRAINTWISTER_RECORD( record_name, \
  (( entry_type, entry_name, entry_default_value )) \
     ... \
)
```

for example a database connection record can be defined as

```
BRAINTWISTER_RECORD( Database, \
  (( uint16_t, port, 3306 )) \
  (( std::string, database, "" )) \
  (( std::string, table, "" )) \
)
```

The entries are statically typed and are directly accessible using the dot operator

```
Database db;
std::cout << db.database << std::endl;
```

A record can be initialized with a build pattern

```
Database db.set_port(9876);
```

or with JSON/XML

```
{
  "port": 9876,
  "database": "staff",
  "table": "employees"
}
```

Nested records and std::vector are supported.


Polymorphic record
------------------

For a polymorphic record a macro for the base class and for
the derived classes have to be defined by

```
BRAINTWISTER_RECORD_BASE( base_recor_name, \
 (( base_entry_type, base_entry_name, base_entry_default_value )) \
 ..., \
 virtual function \
)

BRAINTWISTER_RECORD_DERIVED( derived_record_name, \
 (( derived_entry_type, derived_entry_name, derived_entry_default_value )) \
 ..., \
 virtual function \
)
```

Requirements
------------

- Boost preprocessor
- Boost property-tree
- Google-test (optional)

conan.io
--------

C++ conan.io package is available at https://api.bintray.com/conan/braintwister/conan
