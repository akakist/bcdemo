#include "blockchainNodeService.h"

void BlockchainNode::Service::initDB(st_TRANSACTION *tr)
{
    MUTEX_INSPECTOR;


    tr->dbh->execSimple((QUERY)"CREATE TABLE  IF NOT EXISTS ? "
                    "("
                    "id BIGINT UNIQUE,"
                     "body blob,"
                    "KEY(id) "
                    ")"
                    "ENGINE=InnoDB DEFAULT CHARSET=utf8"
                    <<TBL_BLOCK
                   );




}
