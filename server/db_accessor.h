#pragma once

#include "logger.h"
#include "structs.h"
#include <boost/asio/spawn.hpp>
#include <optional>
#include <ozo/connection.h>
#include <ozo/connection_info.h>
#include <ozo/connection_pool.h>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

namespace nibaserver {

class db_accessor {
public:
    db_accessor(const ozo::connector<ozo::connection_pool<ozo::connection_info<>>,
                                     ozo::connection_pool_timeouts> &conn);
    // ~db_accessor() = default;
    bool login(const std::string &id, const std::string &password,
               boost::asio::yield_context &yield);

    bool logout(const std::string &id, boost::asio::yield_context &yield);

    bool create_user(const std::string &id, const std::string &password,
                     boost::asio::yield_context &yield);

    // NOTE no save char functions yet
    std::optional<nibashared::player> get_char(const std::string &id,
                                               boost::asio::yield_context &yield);
    // get player auxiliary data, magic and equipments
    std::pair<std::vector<nibashared::magic>, std::vector<nibashared::equipment>>
    get_aux(const std::string &name, boost::asio::yield_context &yield);
    // create new character
    bool create_char(const std::string &id, const nibashared::player &player,
                     boost::asio::yield_context &yield);

private:
    // TODO: move char_tbl_ into db
    logger logger_;
    std::unordered_map<std::string, nibashared::character> char_tbl_;
    const ozo::connector<ozo::connection_pool<ozo::connection_info<>>,
                         ozo::connection_pool_timeouts> &conn_;
};

} // namespace nibaserver
