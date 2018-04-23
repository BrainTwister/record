from conans import ConanFile, CMake

class CppsettingsConan(ConanFile):
    
    name = "cpp-settings"
    version = "0.2"
    
    # No settings/options are necessary, this is header only
    exports_sources = "include/*"
    no_copy_source = True
    
    settings = "os", "compiler", "build_type", "arch"
    requires = \
        "boost_preprocessor/1.66.0@bincrafters/stable", \
        "boost_property_tree/1.66.0@bincrafters/stable", \
        "gtest/1.8.0@bincrafters/stable"
    generators = "cmake"
    default_options = "Boost:header_only=True"

    def build(self): # this is not building a library, just tests
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.test()

    def package(self):
        self.copy("*.h")

    def package_id(self):
        self.info.header_only()
