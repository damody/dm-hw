#include "log_define.h"
#include <iomanip>

void log_init()
{
	logging::init_log_to_console();
	typedef sinks::synchronous_sink< sinks::text_ostream_backend > text_sink;
	boost::shared_ptr< text_sink > pSink = boost::make_shared< text_sink >();
	pSink->locked_backend()->add_stream(
		boost::make_shared< std::ofstream >("dm.log"));
	pSink->locked_backend()->auto_flush(true);
	pSink->locked_backend()->set_formatter
		(
		fmt::stream
		// line id will be written in hex, 8-digits, zero-filled
		<< fmt::attr< unsigned int >("LineID", keywords::format = "%03d")
		<< ": <" << fmt::attr< logging::trivial::severity_level >("Severity")
		<< ">\t" << fmt::message()
		);
	logging::core::get()->add_sink(pSink);
	LOG_TRACE.precision(9);
}
