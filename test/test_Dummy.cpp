#include <boost/test/unit_test.hpp>
#include <path2d_view/Dummy.hpp>

using namespace path2d_view;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    path2d_view::DummyClass dummy;
    dummy.welcome();
}
