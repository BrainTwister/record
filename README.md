C++ settings
============

- Type safe members
- Easy access over member name
- Mandatory default value
- Support polymorphic classes
- Serialization via markup language (e.g. json, yml, xml)

Define settings class
---------------------

A settings class will be defined with the macro

    BRAINTWISTER_SETTINGS( Name, \
      (( member_type, member_name, member_default_value )) \
      ... \
    )
    