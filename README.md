BrainTwister Record
===================

A record is a linear, direct-access data structure with heterogeneous entries.
In C++ a record is typically related to a passive data structure (PDS), which is a class or a struct with only public members.

```
struct Database
{
    uint16_t, port;
    std::string database;
    std::string host;
} 
```

A record has statically typed fields, which are directly accessible using the dot operator.

A BrainTwister Record provides some useful additional features.


Functional requirements
-----------------------

- All data members are defined with static types (member_type)
- All data members are directly accessible using the member_name
- All data members have a mandatory default value (member_default_value)
- Arrays will be supported
- Nested structures will be supported
- Polymorphic structures will be supported
- Data structures can be serialization via markup language (e.g. json, xml, yml)

Define settings class
---------------------

A settings class is defined by

    BRAINTWISTER_RECORD( record_name, \
      (( field_type, field_name, field_default_value )) \
      ... \
    )

for example settings for a database

    BRAINTWISTER_RECORD( Database, \
      (( uint16_t, port, 3306 )) \
      (( std::string, database, "" )) \
      (( std::string, table, "" )) \
      ... \
    )

Polymorphic settings
--------------------

A base class is defined by

    BRAINTWISTER_SETTINGS_BASE( BaseName, \
	  (( base_member_type, base_member_name, base_member_default_value )) \
	  ..., \
	  virtual function \
    )

A derived class is defined by

    BRAINTWISTER_SETTINGS_DERIVED( DerivedName, \
	  (( derived_member_type, derived_member_name, derived_member_default_value )) \
	  ..., \
	  virtual function \
    )

Serialization to markup language
--------------------------------

The data of the example 'DatabaseSettings' can be read from JSON:

    {
      "port": 9876,
      "database": "staff",
      "table": "employees"
    }

or a more complex example:

    {
      "benchmark_settings": {
        "min_replications": 3,
        "min_execution_time_in_milliseconds": 10,
        "spike_detection": 0.1
      },
      "actions": [
        {"MatrixMatrixMultiplication": {
          "matrix_types": [{"A": "Matrix<Dense, double>", "B": "Matrix<Dense, double>"}],
          "sizes": [100, 200, 400, 800, 1600, 3200],
          "occupations": [1.0],
          "interfaces": ["IntelMKL", "OpenBLAS"]
        }},
        {"MatrixMatrixMultiplication": {
          "matrix_types": [{"A": "Matrix<Sparse, double>", "B": "Matrix<Sparse, double>"}],
          "sizes": [100, 200, 400, 800, 1600, 3200],
          "occupations": [1.0, 0.5, 0.1, 0.01],
          "interfaces": ["IntelMKL", "Native"]
        }}
      ],
      "reporters": [
        {"StandardReporter": {
          "verbosity": 3
        }},
        {"DatabaseReporter": {
          "verbosity": 3,
          "port": 9876,
          "database": "benchmarks",
          "table": "matmatmult"
        }}
      ]
    }
