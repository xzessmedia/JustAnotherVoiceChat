/*
 * File: include/protocol.h
 * Date: 13.02.2018
 *
 * MIT License
 *
 * Copyright (c) 2018 JustAnotherVoiceChat
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <sstream>

#define ENET_PORT 23332
#define HTTP_PORT 23333

#define NETWORK_CHANNELS 3
#define NETWORK_HANDSHAKE_CHANNEL 0
#define NETWORK_UPDATE_CHANNEL 1
#define NETWORK_STATUS_CHANNEL 2

#define STATUS_CODE_OK 0
#define STATUS_CODE_UNKNOWN_ERROR 1
#define STATUS_CODE_NOT_CONNECTED_TO_SERVER 2
#define STATUS_CODE_NOT_MOVED_TO_CHANNEL 3
#define STATUS_CODE_UNABLE_TO_MUTE_CLIENTS 4

typedef struct {
  uint16_t teamspeakId;
  float x;
  float y;
  float z;

  template <class Archive>
  void serialize(Archive &ar) {
    ar(CEREAL_NVP(teamspeakId), CEREAL_NVP(x), CEREAL_NVP(y), CEREAL_NVP(z));
  }
} clientPositionUpdate_t;

typedef struct {
  uint16_t teamspeakId;
  bool muted;
  float volume;

  template <class Archive>
  void serialize(Archive &ar) {
    ar(CEREAL_NVP(teamspeakId), CEREAL_NVP(muted), CEREAL_NVP(volume));
  }
} clientVolumeUpdate_t;

typedef struct {
  int statusCode;
  std::string reason;

  std::string teamspeakServerUniqueIdentifier;

  uint64_t channelId;
  std::string channelPassword;

  template <class Archive>
  void serialize(Archive &ar) {
    ar(CEREAL_NVP(statusCode), CEREAL_NVP(reason), CEREAL_NVP(teamspeakServerUniqueIdentifier), CEREAL_NVP(channelId), CEREAL_NVP(channelPassword));
  }
} handshakeResponsePacket_t;

typedef struct {
  uint16_t gameId;
  uint16_t teamspeakId;
  int statusCode;

  int versionMajor;
  int versionMinor;
  int versionPatch;
  int versionBuild;

  template <class Archive>
  void serialize(Archive &ar) {
    ar(CEREAL_NVP(gameId), CEREAL_NVP(teamspeakId), CEREAL_NVP(statusCode), CEREAL_NVP(versionMajor), CEREAL_NVP(versionMinor), CEREAL_NVP(versionPatch), CEREAL_NVP(versionBuild));
  }
} handshakePacket_t;

typedef struct {
  std::vector<clientPositionUpdate_t> positions;
  std::vector<clientVolumeUpdate_t> volumes;

  template <class Archive>
  void serialize(Archive &ar) {
    ar(CEREAL_NVP(positions), CEREAL_NVP(volumes));
  }
} updatePacket_t;

typedef struct {
  bool talking;
  bool microphoneMuted;
  bool speakersMuted;

  template <class Archive>
  void serialize(Archive &ar) {
    ar(CEREAL_NVP(talking), CEREAL_NVP(microphoneMuted), CEREAL_NVP(speakersMuted));
  }
} statusPacket_t;
