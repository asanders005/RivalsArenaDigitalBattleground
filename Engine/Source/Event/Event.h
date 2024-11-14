#pragma once
#include "EventData.h"

#include <string>
#include <variant>
#include <memory>

using id_t = std::string;

struct Event
{
	Event(const id_t& id, const EventData& data) : id{ id }, data{ data } {}

	id_t id;
	EventData data;
};