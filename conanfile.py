from conans import ConanFile, CMake, tools

class CppsettingsConan(ConanFile):
    name = "cpp-settings"
    version = "0.2"
    # No settings/options are necessary, this is header only
    exports_sources = "include/*"
    no_copy_source = True

    def package(self):
        self.copy("*.h")
