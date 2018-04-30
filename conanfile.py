from conans import ConanFile, CMake

class RecordConan(ConanFile):
    
    name = "record"
    version = "1.0"
    
    exports_sources = "include/*"
    no_copy_source = True
    
    settings = "os", "compiler", "build_type", "arch"
    requires = \
        "boost_preprocessor/1.66.0@bincrafters/stable", \
        "boost_property_tree/1.66.0@bincrafters/stable", \
        "gtest/1.8.0@bincrafters/stable"
    generators = "cmake"
    default_options = "Boost:header_only=True"

    def build(self):
        # This is not building a library, just test
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.test()

    def package(self):
        self.copy("*.h")

    def package_id(self):
        self.info.header_only()
