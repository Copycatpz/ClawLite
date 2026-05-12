// ClawLite — 会话存储测试
// TODO: B 同学补充测试用例

#include "memory/session_store.h"
#include <iostream>
#include <cassert>

using namespace clawlite;

void testSessionCrud() {
    SessionStore store;

    store.createSession("agent:main:cli:user:default");
    assert(store.hasSession("agent:main:cli:user:default"));
    assert(store.sessionCount() == 1);

    store.appendMessage("agent:main:cli:user:default", Message::user("Hello"));
    store.appendMessage("agent:main:cli:user:default", Message::assistant("Hi!"));

    auto history = store.getHistory("agent:main:cli:user:default", 10);
    assert(history.size() == 2);
    assert(history[0].role == Role::User);
    assert(history[1].role == Role::Assistant);

    store.clear();
    std::cout << "  [PASS] testSessionCrud\n";
}

void testParseSessionKey() {
    auto info = SessionStore::parseSessionKey("agent:main:cli:user:default");
    assert(info.agentId == "main");
    assert(info.channel == "cli");
    assert(info.peerKind == "user");
    assert(info.peerId == "default");
    std::cout << "  [PASS] testParseSessionKey\n";
}

void testBuildSessionKey() {
    std::string key = SessionStore::buildSessionKey("main", "cli", "user", "default");
    assert(key == "agent:main:cli:user:default");
    std::cout << "  [PASS] testBuildSessionKey\n";
}

void testListByAgent() {
    SessionStore store;
    store.createSession("agent:main:cli:user:u1");
    store.createSession("agent:main:cli:user:u2");
    store.createSession("agent:other:cli:user:u1");

    auto sessions = store.listSessionsByAgent("main");
    assert(sessions.size() == 2);

    store.clear();
    std::cout << "  [PASS] testListByAgent\n";
}

int run_session_store_tests() {
    std::cout << "Session Store Tests:\n";
    testSessionCrud();
    testParseSessionKey();
    testBuildSessionKey();
    testListByAgent();
    std::cout << "All session store tests passed.\n";
    return 0;
}
