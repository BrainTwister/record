C++ settings
============

- Type safe members
- Easy access over member name
- Mandatory default value
- Support polymorphic classes
- Serialization via markup language (e.g. json, yml, xml)

Define settings class
---------------------

A settings class is defined by

    BRAINTWISTER_SETTINGS( Name, \
      (( member_type, member_name, member_default_value )) \
      ... \
    )

for example settigs for a database

    BRAINTWISTER_SETTINGS( DatabaseSettings, \
      (( std::string, database, "" )) \
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

The data of the example 'DatabaseSettings' can be read in from JSON

    {
      "port": 3306,
      "database": "staff",
      "table": "employees"
    }
