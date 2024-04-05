#include <iostream>
#include <CLS.pb.h>
#include <sstream>

std::ostream& operator<< ( std::ostream& s, cls_gen::BusinessRequest const& r);



/*
#include <string_view>

std::string_view tab1 ("  ");
std::string_view tab2 ("    ");
std::string_view tab3 ("      ");

namespace cls_core{

    template <class T> 
    T& operator<< ( T& s, cls_gen::BusinessRequest& r){
        s << "businesRquest\n[";
        s << tab1 << "clientRequestId: " << r.clientrequestid() << "\n"; 
        s << tab1 << "context" << "\n";
        s << tab1 << "[" << "\n";
        s << tab2 << "traceId:" << r.context().traceid();
        s << tab1 << "]" << "\n";
    //....
    s <<"]";
    return s;
    }

}

*/