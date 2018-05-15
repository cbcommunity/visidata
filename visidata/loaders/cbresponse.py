from visidata import *
from cbapi.response import *
from cbapi.response.models import CbChildProcEvent, CbFileModEvent, CbNetConnEvent, CbRegModEvent, CbModLoadEvent, CbCrossProcEvent
from cbapi.errors import ObjectNotFoundError

# import logging
# logging.basicConfig()
# logging.getLogger("cbapi").setLevel(logging.DEBUG)


def open_cbresponse(path, group_by_id, sort_by):
    cb = CbResponseAPI()
    vs = CbResponseSheet(cb, path, group_by_id, sort_by)
    vs.columns = ArrayNamedColumns(["id", "start", "username", "hostname", "cmdline"])
    return vs


def event_summary(event):
    timestamp = str(event.timestamp)
    if type(event) == CbFileModEvent:
        return [event.parent.process_name, timestamp, event.type, event.path, '']
    elif type(event) == CbNetConnEvent:
        if event.domain:
            hostname = event.domain
        else:
            hostname = event.remote_ip
        hostname += ':%d' % event.remote_port

        return [event.parent.process_name, timestamp, event.direction + ' netconn', hostname, '']
    elif type(event) == CbRegModEvent:
        return [event.parent.process_name, timestamp, event.type, event.path, '']
    elif type(event) == CbChildProcEvent:
        try:
            childproc = event.process.cmdline
        except ObjectNotFoundError:
            childproc = "<unknown>"
        return [event.parent.process_name, timestamp, 'childproc', event.path, childproc]
    elif type(event) == CbModLoadEvent:
        return [event.parent.process_name, timestamp, 'modload', event.path, event.md5]
    elif type(event) == CbCrossProcEvent:
        return [event.source_path, timestamp, event.type, event.target_path, event.privileges]
    else:
        return None


class CbResponseSheet(Sheet):
    commands = [
        Command(ENTER, 'vd.push(sheet.getProcessDetails(cursorRow[0]))', 'Get details for the given process'),
        Command("ALT-BUTTON1_RELEASED", 'sheet.launchBrowser(cursorRow[0])', 'Launch web browser to view process'),
    ]
    def __init__(self, cb, querystring, group_by_id, sort_by):
        super().__init__("CbResponse", source=querystring, tableName=f"Process Query: {querystring}")
        self.querystring = querystring
        self.group_by_id = group_by_id
        self.sort_by = sort_by
        self.cb = cb

    @async
    def reload(self):
        query = self.cb.select(Process).where(self.querystring).sort(self.sort_by)
        if self.group_by_id:
            query = query.group_by("id")

        for r in Progress(query):
            row = [str(x) for x in [r.id, r.start, r.username, r.hostname, r.cmdline]]
            self.addRow(row)

    def getProcessDetails(self, procid):
        proc = self.cb.select(Process, procid)
        return CbResponseProcessSheet(self.cb, proc)

    def launchBrowser(self, procid):
        os.system("open {0}".format(self.cb.select(Process, procid).webui_link))


class CbResponseProcessSheet(Sheet):
    columns = ArrayNamedColumns(['ProcessPath', 'Timestamp', 'Event', 'Path/IP/Domain', 'Comments'])

    def __init__(self, cb, proc):
        super().__init__("CbResponse", source=proc.id, tableName=f"Process Details: f{proc.id}")
        self.process = proc
        self.cb = cb

    @async
    def reload(self):
        list_of_segments = self.process.get_segments()

        for segment in Progress(list_of_segments):
            self.process.current_segment = segment
            segment_events = self.process.all_events_segment
            for evt in segment_events:
                self.addRow(event_summary(evt))
