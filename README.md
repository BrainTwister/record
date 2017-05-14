C++ settings
============

- Type safe members
- Easy access over member name
- Mandatory default values
- Support lists and nested structures
- Support polymorphic classes
- Serialization via markup language (e.g. json, xml, yml)

Define settings class
---------------------

A settings class is defined by

    BRAINTWISTER_SETTINGS( Name, \
      (( member_type, member_name, member_default_value )) \
      ... \
    )

for example settigs for a database

    BRAINTWISTER_SETTINGS( DatabaseSettings, \
      (( unsigned int, port, 3306 )) \
      (( std::string, database, "" )) \
      (( std::string, table, "" )) \
      ... \
    )

Polymorphic settings
--------------------

A base class is defined by

    BLASBOOSTER_SETTINGS_BASE( BaseName, \
	  (( base_member_type, base_member_name, base_member_default_value )) \
	  ..., \
	  virtual function \
    )

A derived class is defined by

    BLASBOOSTER_SETTINGS_DERIVED( DerivedName, \
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