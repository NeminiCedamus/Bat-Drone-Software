#ifndef CMD_TLM_HPP
#define CMD_TLM_HPP
#include "commands.hpp"
#include <stdint.h>
#include <vector>

using namespace std;

class PacketReader;
class PacketWriter;
class ControlPacketElement;

class Point {
public:
  float x, y;
  Point(float x, float y) : x(x), y(y) {
  }
};

class TrackerPoint : public Point {
public:
  int id;
  TrackerPoint(int id, float x, float y) : Point(x, y), id(id) {}
};

/**
 * This class handles communication using PacketWriter and PacketReader classes.
 */
class CmdTlm : public Commands {
private:
  PacketReader *packetReader;
  PacketWriter *packetWriter;
public:
  CmdTlm(PacketReader *reader, PacketWriter *writer);
  virtual void telemetry(Commands &callback);
  virtual void control(const ControlPacketElement &e);
  virtual void lwirFrame(const uint16_t frame[60][80]);
};

#endif
