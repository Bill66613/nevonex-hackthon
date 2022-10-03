from conans import ConanFile, CMake, tools
import os


class NevonexHackathon(ConanFile):

    name = "nevonex-hackathon"
    version = "1.0.0"
    license = "commercial"
    author = "Nguyen Truong Minh Hoang (MS/EJV31-PS), FIXED-TERM Tran Hoai Duong (MS/EJV31-PS), Lam Hau Huong (MS/EJV31-PS)"
    description = "Nevonex Hackathon 1.0"
    url = "https://github.com/Bill66613/nevonex-hackthon"
    topics = ["hackathon", "conan"]
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"
    repo_package_mapping = {}
    options = {"shared": [True, False]}
    default_options = {"shared": False}
    exports_sources = ["src/*", "CMakeLists.txt"]
    configs = {}
    requires = [
    ]
    repos = []

    def config_options(self):
        self.settings.compiler.libcxx = 'libstdc++11'

    def build(self):

        cmake = CMake(self)
        cmake.definitions["PLUGIN_VERSION"] = self.version
        cmake.definitions["COVERAGE"] = os.getenv("COVERAGE", 0)
        cmake.configure(source_folder=".")
        cmake.build()

    def imports(self):
        self.copy("*.so*", keep_path=True)
        self.copy("*.a*", keep_path=True)
        self.copy("*.h", keep_path=True)
        self.copy("*.hpp", keep_path=True)

    def package(self):
        self.copy("*.so", dst="plugins/", src="lib/", keep_path=True)

    def package_info(self):
        self.cpp_info.libs = ["nevonex_hackathon"]
