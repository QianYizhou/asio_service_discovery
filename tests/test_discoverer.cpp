#include <betabugs/networking/service_discoverer.hpp>

int main(int argc, const char *const argv[]) {
  (void)argc;
  (void)argv;

  // boost::asio::io_service io_service;
  // betabugs::networking::service_announcer announcer(io_service, "my_service",
  // 1337); io_service.run();

  boost::asio::io_service io_service;
  betabugs::networking::service_discoverer discoverer(
      io_service, "my_service",
      [](const betabugs::networking::service_discoverer::services &services) {
        std::clog << "my_service is available on the following machines:"
                  << std::endl;
        for (const auto &service : services) {
          std::clog << "  " << service << std::endl;
        }
      });
  io_service.run();

  return 0;
}
