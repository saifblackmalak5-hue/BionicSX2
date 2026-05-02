// BionicSX2 iOS stub for discord_rpc.h
#pragma once
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef struct DiscordRichPresence {
    const char* state;
    const char* details;
    int64_t startTimestamp;
    int64_t endTimestamp;
    const char* largeImageKey;
    const char* largeImageText;
    const char* smallImageKey;
    const char* smallImageText;
    const char* partyId;
    int partySize;
    int partyMax;
    const char* matchSecret;
    const char* joinSecret;
    const char* spectateSecret;
    int8_t instance;
} DiscordRichPresence;
typedef struct DiscordUser {
    const char* userId;
    const char* username;
    const char* discriminator;
    const char* avatar;
} DiscordUser;
typedef struct DiscordEventHandlers {
    void (*ready)(const DiscordUser*);
    void (*disconnected)(int, const char*);
    void (*errored)(int, const char*);
    void (*joinGame)(const char*);
    void (*spectateGame)(const char*);
    void (*joinRequest)(const DiscordUser*);
} DiscordEventHandlers;
static inline void Discord_Initialize(const char*, DiscordEventHandlers*, int, const char*) {}
static inline void Discord_Shutdown(void) {}
static inline void Discord_RunCallbacks(void) {}
static inline void Discord_UpdatePresence(const DiscordRichPresence*) {}
static inline void Discord_ClearPresence(void) {}
static inline void Discord_Respond(const char*, int) {}
static inline void Discord_UpdateHandlers(DiscordEventHandlers*) {}
#ifdef __cplusplus
}
#endif
