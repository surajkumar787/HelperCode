// Copyright Koninklijke Philips N.V., 2025. All Rights Reserved

#pragma once

#include <net/http.h>

namespace Philips::IGT::A2D::Components::Utility {

class HttpClient : public Net::Http::Client
{
public:
    HttpClient(const Net::IpAddress& ipAddress)
        : Net::Http::Client(ipAddress)
    {
    }
    Net::Future<Client::Response> sendRequest(Net::Http::Header header)
    {
        return sendRecv(std::move(header)).second;
    }
};

} // namespace Philips::IGT::A2D::Components::Utility
