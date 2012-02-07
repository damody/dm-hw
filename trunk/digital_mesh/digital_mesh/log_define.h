#pragma once
#pragma warning( push, 0 )
#include <boost/filesystem.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/filters.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/common.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/utility/string_literal.hpp>
#include <boost/log/utility/type_info_wrapper.hpp>
#include <boost/log/utility/init/to_console.hpp>
#include <boost/log/utility/init/to_file.hpp>
#include <boost/log/utility/init/common_attributes.hpp>
#include <boost/log/utility/init/filter_parser.hpp>
#include <boost/log/utility/init/formatter_parser.hpp>
#include <boost/log/formatters/stream.hpp>
#include <boost/log/formatters/format.hpp>
#include <boost/log/formatters/attr.hpp>
#include <boost/log/formatters/date_time.hpp>
#include <boost/log/formatters/named_scope.hpp>
#include <boost/log/formatters/if.hpp>
#include <boost/log/formatters/message.hpp>
#include <boost/log/formatters/xml_decorator.hpp>
#pragma warning( pop ) 

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace src = boost::log::sources;
namespace fmt = boost::log::formatters;
namespace flt = boost::log::filters;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;

void log_init();

#define LOG_TRACE	BOOST_LOG_TRIVIAL(trace)
#define LOG_DEBUG	BOOST_LOG_TRIVIAL(debug)
#define LOG_INFO	BOOST_LOG_TRIVIAL(info)
#define LOG_WARNING	BOOST_LOG_TRIVIAL(warning)
#define LOG_ERROR	BOOST_LOG_TRIVIAL(error)
#define LOG_FATAL	BOOST_LOG_TRIVIAL(fatal)
