#ifndef _______HTTTP___SERVICE____EVENT_______H12BCINV
#define _______HTTTP___SERVICE____EVENT_______H12BCINV
#include "eventEnum.h"
#include "event_mt.h"

#include "serviceEnum.h"
#include <string>
#include "EVENT_id.h"
#include "SERVICE_id.h"
namespace ServiceEnum
{
    const SERVICE_id IMInvoicer("im.IMInvoicer");

}

namespace invoiceEventEnum
{
    const EVENT_id GetInvoiceREQ("im.GetInvoiceREQ");
    const EVENT_id GetInvoiceRSP("im.GetInvoiceRSP");
    const EVENT_id MakeInvoiceREQ("im.MakeInvoiceREQ");
    const EVENT_id MakeInvoiceRSP("im.MakeInvoiceRSP");
}


#endif
