from conans import ConanFile, CMake

class RecordConan(ConanFile):
    
    name = "record"
    version = "1.2"
    license = "MIT"
    description = "A heterogeneous data structure for C++"
    homepage = "https://braintwister.eu"
    url = "https://github.com/braintwister/record.git"
    
    exports_sources = "include/*", "test/*", "CMakeLists.txt"
    no_copy_source = True
    
    settings = "os", "compiler", "build_type", "arch"
    requires = \
        "boost/1.71.0", \
        "gtest/1.8.1"
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
