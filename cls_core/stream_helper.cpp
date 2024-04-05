#include <stream_helper.h>

#include <string_view>

std::string_view tab1 ("  ");
std::string_view tab2 ("    ");
std::string_view tab3 ("      ");
std::string_view tab4 ("        ");
std::ostream& operator<< ( std::ostream& s, cls_gen::BusinessRequest const& r) {

    s << "businesRquest\n[";
    s << tab1 << "clientRequestId: " << r.clientrequestid() << "\n"; 
    s << tab1 << "context" << "\n";
    s << tab1 << "[" << "\n";
    if (r.context().has_traceid()) s << tab2 << "traceId:" << r.context().traceid() << "\n";
    s << tab1 << "]" << "\n";
    //....
    s <<"]" << "\n";
    return s;
}

