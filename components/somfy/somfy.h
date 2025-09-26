#pragma once

#include "esphome/core/preferences.h"
#include "esphome/components/remote_transmitter/remote_transmitter.h"
#include "esphome/components/remote_receiver/remote_receiver.h"

namespace esphome {
namespace somfy {

enum SomfyCommand : uint16_t {
    SOMFY_POWER = 0x11,
    SOMFY_UP = 0x21,
    SOMFY_MYUP = 0x22,
    SOMFY_DOWN = 0x23,
    SOMFY_MYDOWN = 0x24,
    SOMFY_UPDOWN = 0x25,
    SOMFY_MYUPDOWN = 0x26,
    SOMFY_PROG = 0x27,
    SOMFY_SUNFLAG = 0x31,
    SOMFY_FLAG = 0x32,
    SOMFY_STEPDOWN = 0x33,
    SOMFY_TOGGLE = 0x34,
    SOMFY_SENSOR = 0x41,
};

class SomfySensor {
 public:
  virtual void update_sunny(uint32_t address, bool value) {}
  virtual void update_windy(uint32_t address, bool value) {}
};

class SomfyComponent : public Component, public remote_base::RemoteReceiverListener {
 public:
  float get_setup_priority() const override { return setup_priority::LATE; }
  void setup() override;
  void dump_config() override;
  bool on_receive(remote_base::RemoteReceiveData data) override;
  void send_command(SomfyCommand command, uint32_t repeat = 4);
  void set_code(uint16_t code);
  void set_tx(remote_transmitter::RemoteTransmitterComponent *tx) { this->tx_ = tx; }
  void set_rx(remote_receiver::RemoteReceiverComponent *rx) { this->rx_ = rx; }
  void set_address(uint32_t address) { this->address_ = address; }
  void add_sensor(SomfySensor *sensor) { this->sensors_.push_back(sensor); }
 protected:
  remote_transmitter::RemoteTransmitterComponent *tx_{nullptr};
  remote_receiver::RemoteReceiverComponent *rx_{nullptr};
  ESPPreferenceObject preferences_;
  uint32_t address_;
  uint16_t code_;
  std::vector<SomfySensor *> sensors_;
};

}  // namespace acurite
}  // namespace esphome
