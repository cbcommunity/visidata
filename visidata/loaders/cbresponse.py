from visidata import *
from cbapi.response import *

# import logging
# logging.basicConfig()
# logging.getLogger("cbapi").setLevel(logging.DEBUG)


def open_cbresponse(path):
    cb = CbResponseAPI()
    vs = CbResponseSheet(cb, path)
    vs.columns = ArrayNamedColumns(["start", "username", "hostname", "cmdline"])
    return vs


class CbResponseSheet(Sheet):
    def __init__(self, cb, querystring):
        super().__init__("CbResponse", source=querystring, tableName="Process")
        self.querystring = querystring
        self.cb = cb

    @async
    def reload(self):
        query = self.cb.select(Process).where(self.querystring)
        for r in Progress(query, total=len(query)):
            row = [str(x) for x in [r.start, r.username, r.hostname, r.cmdline]]
            self.addRow(row)

