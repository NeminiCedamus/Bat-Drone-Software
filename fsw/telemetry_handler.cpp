#include "telemetry_handler.hpp"
#include "pt1.h"
#include "cmd_tlm.hpp"

TelemetryHandler::TelemetryHandler(CmdTlm *cmdtlm, const char *pt1Device) : cmdtlm(cmdtlm), run(true) {
  pt1_init(pt1Device);
}

TelemetryHandler::~TelemetryHandler() {
  pt1_deinit();
}

void TelemetryHandler::startThread() {
  tlm_thread = thread(&TelemetryHandler::mainLoop, this);
}

void TelemetryHandler::stopThread() {
  run = false;
}

void TelemetryHandler::joinThread() {
  tlm_thread.join();
}

void TelemetryHandler::mainLoop() {
  pt1_start();
  while (run) {
    pt1_frame frame;
    pt1_get_frame(&frame);
    cmdtlm->lwirFrame((const uint16_t (*)[80])frame.start);
  }
  pt1_stop();
}
