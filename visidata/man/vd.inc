.Dd January 24, 2017
.Dt vd \&1 "Quick Reference Guide" 
.Os Linux/MacOS
.
.\" Long option with arg: .Lo f filetype format
.\" Long flag: .Lo f filetype
.de Lo
.It Cm -\\$1 Ns , Cm --\\$2 Ns = Ns Ar \\$3
..
.de Lf
.It Cm -\\$1 Ns , Cm --\\$2
..
.Sh NAME
.
.Nm VisiData
.Nd a terminal utility for exploring and arranging tabular data
.
.Sh SYNOPSIS
.
.Nm vd
.Op Ar options
.Op Ar input No ...
.
.Nm vd
.Op Ar options
.Cm --play Ar cmdlog
.Op Cm -w Ar waitsecs
.Op Cm --batch
.Op Cm -o Ar output
.Op Ar field Ns Cm = Ns Ar value No ...
.
.Sh DESCRIPTION
.Nm VisiData
is a multipurpose tool for exploring, cleaning, editing, and restructuring data.
Rows can be selected, filtered, and grouped; columns can be rearranged, transformed, and derived via regex or Python expressions; workflows can be saved, documented, and replayed.
.Nm VisiData No is built on the Sy vdtui No platform.
.
.Ss REPLAY MODE
.Bl -tag -width XXXXXXXXXXXXXXXXXXXXXX -compact
.Lo p play cmdlog
.No replays a saved Ar cmdlog No within the interface
.
.Lo w replay-wait seconds
.No waits Ar seconds No between commands
.
.Lf b batch
replays in batch mode (with no interface)
.
.Lo o output file
.No saves final visible sheet to Ar file No as .tsv
.
.It Sy --replay-movement= Ns Ar bool
.No toggles Sy --play No to move cursor cell-by-cell
.It Ar field Ns Cm = Ns Ar value
.No replaces \&"{ Ns Ar field Ns }\&" in Ar cmdlog No contents with Ar value
.El
.
.Ss Commands During Replay
.Bl -tag -width XXXXXXXXXXXXXXXXXXX -compact -offset XXX
.It Sy ^U
pauses/resumes replay
.It Sy Tab
executes next row in replaying sheet
.It Sy ^K
cancels current replay
.El
.
.Ss GLOBAL COMMANDS
In most cases, commands that affect 'selected rows' will affect all rows if no rows are selected.
.Pp
.Ss Keystrokes For The Cautious
.Bl -tag -width XXXXXXXXXXXXXXX -compact
.It Ic " F1   z?"
views this man page
.It Ic "gF1  gz?"
views all commands available on current sheet
.It Ic ^Q
aborts program immediately
.It Ic ^C
cancels user input or aborts all async threads on current sheet
.It Ic " q"
quits current sheet
.It Ic "gq"
quits all sheets (clean exit)
.El
.Ss "Cursor Movement"
.
.Bl -tag -width XXXXXXXXXXXXXXX -compact
.
.It Ic "Arrow PgUp Home"
moves as expected
.It Ic " h   j   k   l"
moves left/down/up/right
.It Ic "gh  gj  gk  gl"
moves all the way to the left/bottom/top/right
.It Ic "     G  gg"
moves all the way to the bottom/top
.It Ic "^B  ^F"
scrolls one page back/forward
.Pp
.It Ic  " /   ?" Ar regex
.No searches for Ar regex No forward/backward in current column
.It Ic  "g/  g?" Ar regex
.No searches for Ar regex No forward/backward over all visible columns
.It Ic  " n   N"
moves to next/previous match from last search
.Pp
.It Ic  " <   >"
moves up/down the current column to the next value
.It Ic " {   }"
moves up/down the current column to the next selected row
.
.El
.Pp
.Bl -tag -width XXXXXXXXXXXXXXX -compact
.Pp
.It Ic " c" Ar regex
.No moves to the next column with name matching Ar regex
.It Ic " r" Ar regex
.No moves to the next row with key matching Ar regex
.It Ic "zc  zr" Ar number
.No moves to given column/row Ar number
.Pp
.It Ic " H   J   K   L"
slides current row/column left/down/up/right
.It Ic "gH  gJ  gK  gL"
slides current row/column all the way to the left/bottom/top/right of sheet
.Pp
.It Ic "zh  zj  zk  zl"
scrolls one left/down/up/right
.It Ic "  zt  zz  zb  "
scrolls current row to top/center/bottom of screen
.El
.
.Ss Column Manipulation
.
.Bl -tag -width XXXXXXXXXXXXXXX -compact
.
.It Ic " _" Ns " (underscore)"
adjusts width of current column
.It Ic "g_"
adjusts width of all visible columns
.It Ic "z_" Ar number
.No adjusts width of current column to Ar number
.Pp
.It Ic " -" Ns " (hyphen)"
hides current column (to unhide, go to
.Sy C Ns olumns sheet and Sy e Ns dit its width)
.It Ic "z-" Ns
reduces width of current column by half
.Pp
.It Ic \&! Ns
pins current column on the left as a key column
.It Ic "~  #  %  $  @"
sets type of current column to untyped/int/float/currency/date
.It Ic "  ^"
edits name of current column
.It Ic " g^"
sets names of all unnamed visible columns to contents of selected rows (or current row)
.It Ic " z^"
sets name of current column to contents of current cell
.It Ic "gz^"
sets name of current column to combined contents of current column for selected rows (or current row)
.Pp
.It Ic "  =" Ar expr
.No creates new column from Python Ar expr Ns , with column names as variables
.It Ic " g=" Ar expr
.No sets current column for selected rows to result of Python Ar expr
.It Ic "gz=" Ar expr
.No sets current column for selected rows to the items in result of Python sequence Ar expr
.It Ic " z=" Ar expr
.No sets current cell to result of evaluated Python Ar expr No on current row
.El
.Bl -tag -width XXXXXXXXXXXXXXX -compact
.It Ic " '" Ns " (tick)"
adds a frozen copy of current column with all cells evaluated
.It Ic "g'"
opens a frozen copy of current sheet with all visible columns evaluated
.It Ic "z'  gz'"
adds/resets cache for current/all visible column(s)
.Pp
.It Ic "\&:" Ar regex
.No adds new columns from Ar regex No split; number of columns determined by example row at cursor
.It Ic "\&;" Ar regex
.No adds new columns from capture groups of Ar regex Ns ; also requires example row
.It Ic "*" Ar regex Ns Sy / Ns Ar subst
.No replaces Ar regex No with Ar subst Ns , which may include backreferences ( Ns Sy \e1 No etc)
.El
.Ss Row Selection
.
.Bl -tag -width XXXXXXXXXXXXXXX -compact
.
.It Ic " s   t   u"
selects/toggles/unselects current row
.It Ic "gs  gt  gu"
selects/toggles/unselects all rows
.It Ic " |   \e\ " Ns Ar regex
.No selects/unselects rows matching Ar regex No in current column
.It Ic "g|  g\e\ " Ns Ar regex
.No selects/unselects rows matching Ar regex No in any visible column
.It Ic " \&," Ns " (comma)"
selects rows matching current cell in current column
.It Ic "g\&,"
selects rows matching this row in all visible columns
.
.El
.
.
.Ss Row Sorting/Filtering
.
.Bl -tag -width XXXXXXXXXXXXXXX -compact
.
.It Ic " [   ]"
sorts ascending/descending by current column
.It Ic "g[  g]"
sorts ascending/descending by all key columns
.It Ic " \&""
opens duplicate sheet with only selected rows
.It Ic "g\&""
opens duplicate sheet with all rows
.It Ic "gz\&""
opens duplicate sheet with deepcopy of selected rows
.El
.Ss Editing Rows and Cells
.
.Bl -tag -width XXXXXXXXXXXXXXX -compact
.It Ic "  a"
appends a blank row
.It Ic " ga" Ar number
.No appends Ar number No blank rows
.It Ic "  d   gd"
deletes current/all selected row(s) and moves to clipboard
.It Ic "  y   gy"
yanks (copies) current/all selected row(s) to clipboard
.It Ic " zy"
yanks (copies) current cell to clipboard
.It Ic "  p    P"
pastes clipboard rows after/before current row
.It Ic " zp  gzp"
sets contents of current column for current/all selected row(s) to last clipboard value
.It Ic "  f"
fills null cells in current column with contents of non-null cells up the current column
.
.
.It Ic "  e" Ar text
edits contents of current cell
.It Ic " ge" Ar text
.No sets contents of current column for selected rows to Ar text
.It Ic " zd   Del"
.No sets contents of current cell to Sy None
.It Ic "gzd  gDel"
.No sets contents of cells in current column to Sy None No for selected rows
.
.El
.
.Ss "  Commands While Editing Input"
.Bl -tag -width XXXXXXXXXXXXXXX -compact -offset XXX
.It Ic "Enter  ^C"
accepts/aborts input
.It Ic ^O
opens external $EDITOR to edit contents
.It Ic ^R
reloads initial value
.It Ic "^A  ^E"
moves to beginning/end of line
.It Ic "^B  ^F"
moves back/forward one character
.It Ic "^H  ^D"
deletes previous/current character
.It Ic ^T
transposes previous and current characters
.It Ic "^U  ^K"
clears from cursor to beginning/end of line
.It Ic "Backspace  Del"
deletes previous/current character
.It Ic Insert
toggles insert mode
.It Ic "Up  Down"
sets contents to previous/next in history
.It Ic "Tab  Shift-Tab"
autocompletes input (when available)
.
.El
.
.Ss Data Toolkit
.Bl -tag -width XXXXXXXXXXXXXXX -compact
.It Ic " o" Ar input
opens
.Ar input No in Sy VisiData
.It Ic "^S" Ar filename
.No saves current sheet to Ar filename No in format determined by extension (default .tsv)
.It Ic "^D" Ar filename.vd
.No saves CommandLog to Ar filename.vd No file
.It Ic "A" Ar number
.No opens new blank sheet with Ar number No columns
.It Ic "R" Ar number
opens duplicate sheet with a random population subset of
.Ar number No rows
.Pp
.It Ic " +" Ar aggregator
.No adds Ar aggregator No to current column (see Sy "Frequency Table" Ns )
.It Ic "z+" Ar aggregator
.No displays result of Ar aggregator No over values in selected rows for current column
.Pp
.El
.Ss Data Visualization
.Bl -tag -width XXXXXXXXXXXXX -compact
.It Ic " ." No (dot)
.No plots current numeric column vs key columns. Numeric key column is used for the x-axis; categorical key column values determine color.
.It Ic "g."
.No plots a graph of all visible numeric columns vs key columns.
.Pp
.El
.No If rows on the current sheet represent plottable coordinates (as in .shp or vector .mbtiles sources),
.Ic " ." No plots the current row, and Ic "g." No plots all selected rows (or all rows if none selected).
.Ss "  Canvas-specific Commands"
.Bl -tag -width XXXXXXXXXXXXXXXXXX -compact -offset XXX
.It Ic " +   -"
increases/decreases zoomlevel, centered on cursor
.It Ic " _" No (underscore)
zooms to fit full extent
.It Ic " s   t   u"
selects/toggles/unselects rows on source sheet contained within canvas cursor
.It Ic "gs  gt  gu"
selects/toggles/unselects rows visible on screen
.It Ic " Enter"
opens sheet of source rows contained within canvas cursor
.It Ic "gEnter"
opens sheet of source rows visible on screen
.It Ic " 1" No - Ic "9"
toggles display of layers
.It Ic "^L"
redraws all pixels on canvas
.It Ic " w"
.No toggles Ic show_graph_labels No option
.It Ic "mouse scrollwheel"
zooms in/out of canvas
.It Ic "left click-drag"
sets canvas cursor
.It Ic "right click-drag"
scrolls canvas
.El
.Ss Other Commands
.
.Bl -tag -width XXXXXXXXXXXXXXX -compact
.
.It Ic V
views contents of current cell in a new TextSheet
.El
.Bl -tag -width XXXXXXXXXXXXXXX -compact -offset xxx
.It Ic "v"
toggles visibility (text wrap on TextSheet, legends/axes on Graph)
.El
.Bl -tag -width XXXXXXXXXXXXXXX -compact
.It Ic " ^^" No (Ctrl-^)
jumps to previous sheet (swaps with current sheet)
.It Ic " ^E"
views traceback for most recent error
.It Ic "g^E"
views traceback for most recent errors
.It Ic "z^E"
views traceback for error in current cell
.It Ic " ^L"
refreshes screen
.It Ic " ^G"
shows cursor position and bounds of current sheet on status line
.It Ic " ^V"
shows version information on status line
.It Ic " ^R"
reloads current sheet
.It Ic "z^R"
clears cache for current column
.It Ic " ^Z"
suspends VisiData process
.It Ic " ^P"
.No opens Sy Status History
.
.El
.Pp
.Bl -tag -width XXXXXXXXXXXXXXX -compact
.It Ic " ^Y  z^Y  g^Y"
opens current row/cell/sheet as Python object
.It Ic " ^X" Ar expr
.No evaluates Python Ar expr No and opens result as python object
.It Ic "z^X" Ar expr
.No evaluates Python Ar expr No on current row and shows result on status line
.It Ic "g^X" Ar stmt
.No executes Python Ar stmt No in the global scope
.El
.
.Ss Internal Sheets List
.Bl -tag -width Xx -compact
.It " "
.It Sy Metasheets
.It Sy " \&."
.Sy Columns Sheet No (Shift-C) "    edit column properties"
.It Sy " \&."
.Sy Sheets Sheet No (Shift-S) "     jump between sheets or join them together"
.It Sy " \&."
.Sy Options Sheet No (Shift-O) "    edit all configurable options"
.It Sy " \&."
.Sy Commandlog No (Shift-D) "       modify and save commands for replay"
.It Sy " \&."
.Sy Error Sheet No (^E) "           view last error"
.It Sy " \&."
.Sy Status History No (^P) "        view history of status messages"
.It Sy " \&."
.Sy Threads Sheet No (^T) "         view, cancel, and profile asynchronous threads"
.Pp
.It Sy Derived Sheets
.It Sy " \&."
.Sy Frequency Table No (Shift-F) "  group rows by column value, with aggregations of other columns"
.It Sy " \&."
.Sy Describe Sheet No (Shift-I) "   view summary statistics for each column"
.It Sy " \&."
.Sy Pivot Table No (Shift-W) "      group rows by key and summarize current column"
.It Sy " \&."
.Sy Melted Sheet No (Shift-M) "     unpivot non-key columns into variable/value columns"
.El
.Ss METASHEETS
.Ss Columns Sheet (Shift-C)
.Bl -inset -compact
.It Properties of columns on the source sheet can be changed with standard editing commands ( Ns Sy e  ge g= Del Ns ) on the Sy Columns Sheet Ns . Multiple aggregators can be set by listing them (separated by spaces) in the aggregators column.  The 'g' commands affect the selected rows, which are actually the literal columns on the source sheet.
.It (global commands)
.El
.Bl -tag -width XXXXXXXXXXXXXXX -compact -offset XXX
.It Ic gC
.No opens Sy Columns Sheet No with all columns from all sheets
.It (sheet-specific commands)
.El
.Bl -tag -width XXXXXXXXXXXXXXX -compact -offset XXX
.It Ic " &"
adds column from concatenating selected source columns
.It Ic " !"
pins current column on the left as a key column on source sheet
.It Ic "g!"
pins selected columns on the left as key columns on source sheet
.It Ic "g+"
adds aggregator to selected source columns
.It Ic "g_" No (underscore)
adjusts widths of selected columns on source sheet
.It Ic "g-" No (hyphen)
hides selected columns on source sheet
.It Ic " ~  #  %  $  @"
sets type of current column on source sheet to str/int/float/currency/date
.It Ic "g~ g# g% g$ g@"
sets type of selected columns on source sheet to str/int/float/currency/date
.It Ic "z~ gz~"
sets type of current/selected column(s) on source sheet to anytype
.It Ic " Enter"
.No opens a Sy Frequency Table No sheet grouped on column referenced in current row
.El
.
.Ss Sheets Sheet (Shift-S)
.Bl -inset -compact 
.It (sheet-specific commands)
.El
.Bl -tag -width XXXXXXXXXXXXXXX -compact -offset XXX
.It Ic "Enter"
jumps to sheet referenced in current row
.It Ic "gC"
.No opens Sy Columns Sheet No with all columns from selected sheets
.It Ic "&" Ar jointype
.No merges selected sheets with visible columns from all, keeping rows according to Ar jointype Ns :
.El
.Bl -tag -width x -compact -offset XXXXXXXXXXXXXXXXXXXX 
.It Sy "\&."
.Sy inner No " keeps only rows which match keys on all sheets"
.It Sy "\&."
.Sy left No "  keeps all rows from first selected sheet"
.It Sy "\&."
.Sy full No "  keeps all rows from all sheets (union)"
.It Sy "\&."
.Sy diff No "  keeps only rows NOT in all sheets"
.It Sy "\&."
.Sy append No "keeps all rows from all sheets (concatenation)"
.El
.
.Ss Options Sheet (Shift-O)
.Bl -inset -compact 
.It (sheet-specific commands)
.El
.Bl -tag -width XXXXXXXXXXXXXXX -compact -offset XXX
.It Ic "Enter"
edits option
.El
.
.Ss CommandLog (Shift-D)
.Bl -inset -compact
.It (sheet-specific commands)
.El
.Bl -tag -width XXXXXXXXXXXXXXX -compact -offset XXX
.It Ic " x"
replays command in current row
.It Ic "gx"
replays contents of entire CommandLog
.It Ic " ^C"
aborts replay
.El
.
.Ss DERIVED SHEETS
.Ss Frequency Table (Shift-F)
.Bl -inset -compact
.It A Sy Frequency Table No groups rows by one or more columns, and includes summary columns for those with aggregators.
.It (global commands)
.El
.Bl -tag -width XXXXXXXXXXXXXXX -compact -offset XXX
.It Ic gF
opens Frequency Table, grouped by all key columns on source sheet
.It Ic zF
opens one-line summary for selected rows
.It (sheet-specific commands)
.It Ic " s   t   u"
selects/toggles/unselects these entries in source sheet
.It Ic " Enter"
opens sheet of source rows which are grouped in current cell
.El
.
.Ss Describe Sheet (Shift-I)
.Bl -inset -compact
.It (sheet-specific commands)
.El
.Bl -tag -width XXXXXXXXXXXXXXX -compact -offset XXX
.It Ic "zs  zu"
selects/unselects rows on source sheet which are being described in current cell
.It Ic " !"
pins current column on the left as a key column on source sheet
.It Ic " Enter"
.No opens a Sy Frequency Table No sheet grouped on column referenced in current row
.It Ic "zEnter"
opens copy of source sheet with rows described in current cell
.El
.
.Ss Pivot Table (Shift-W)
.Bl -inset -compact
.It Set key column(s) and aggregators on column(s) before pressing Sy Shift-W No on the column to pivot.
.It (sheet-specific commands)
.El
.Bl -tag -width XXXXXXXXXXXXXXX -compact -offset XXX
.It Ic " Enter"
opens sheet of source rows aggregated in current pivot row
.It Ic "zEnter"
opens sheet of source rows aggregated in current pivot cell
.El
.Ss Melted Sheet (Shift-M)
.Bl -inset -compact
.It Opens melted sheet (unpivot), with all non-key columns reduced to Variable-Value rows.
.El
.Ss Python Object Sheet (^X ^Y g^Y z^Y)
.Bl -inset -compact
.It (sheet-specific commands)
.El
.Bl -tag -width XXXXXXXXXXXXXXX -compact -offset XXX
.It Ic "Enter"
dives further into Python object
.It Ic "e"
edits contents of current cell
.It Ic "v"
toggles whether methods and hidden properties are shown
.El
.
.Sh COMMANDLINE OPTIONS
.Bl -tag -width XXXXXXXXXXXXXXXXXXXXXXXXXXX -compact
.
.Lo f filetype filetype
.No "tsv               "
uses loader for
.Ar filetype
instead of file extension
.
.Lo y confirm-overwrite F
.No "True              "
overwrites existing files without confirmation
.
.It Cm --diff Ns = Ns Ar base
.No "None              "
.No adds colorizer for all sheets against Ar base
.
.El
.so vd-cli.inc
.
.Ss DISPLAY OPTIONS
.No Display options can only be set via the Sx Options Sheet No or a config file (see Sx FILES Ns ).
.Pp
.
.so vd-opts.inc
.
.Sh EXAMPLES
.Dl Nm vd Cm foo.tsv
.Pp
.Dl Nm vd Cm -f sqlite bar.db
.Pp
.Dl Nm vd Cm postgres:// Ns Ar username Ns Sy "\&:" Ns Ar password Ns Sy @ Ns Ar hostname Ns Sy  "\&:" Ns Ar port Ns Sy / Ns Ar database
.Pp
.Dl Nm vd Cm --play tests/pivot.vd --replay-wait 1 --output tests/pivot.tsv
.Pp
.Dl Ic ls -l | Nm vd Cm -f fixed --skip 1 --header 0
.Pp
.Dl Nm vd --diff foo.tsv bar.tsv
.Pp
.Sh FILES
At the start of every session,
.Sy VisiData No looks for Pa $HOME/.visidatarc Ns , and calls Python exec() on its contents if it exists.
For example:
.Bd -literal
   options.min_memory_mb=100  # stop processing without 100MB free

   globalCommand('0', 'gh')   # alias '0' to move to first column, like vim

   def median(values):
       L = sorted(values)
       return L[len(L)//2]

   aggregator('median', median)
.Ed
.
.Sh SUPPORTED SOURCES
These are the supported sources:
.Pp
.Bl -inset -compact -offset xxx
.It Sy tsv No (tab-separated value)
.Bl -inset -compact -offset xxx
.It Plain and simple.  Nm VisiData No writes tsv format by default.  See the Sy --delimiter No option.
.El
.El
.Pp
.Bl -inset -compact -offset xxx
.It Sy csv No (comma-separated value)
.Bl -inset -compact -offset xxx
.It .csv files are a scourge upon the earth, and still regrettably common.  
.It See the Sy --csv-dialect Ns , Sy --csv-delimiter Ns , Sy --csv-quotechar Ns , and Sy --csv-skipinitialspace No options.  
.It Accepted dialects are Ic excel-tab Ns , Ic unix Ns , and Ic excel Ns .
.El
.El
.Pp
.Bl -inset -compact -offset xxx
.It Sy fixed No (fixed width text)
.Bl -inset -compact -offset xxx
.It Columns are autodetected from the first 1000 rows (adjustable with Sy --fixed-rows Ns ).
.El
.El
.Pp
.Bl -inset -compact -offset xxx
.It Sy json No (single object) and Sy jsonl No (one object per line).
.Bl -inset -compact -offset xxx
.It Cells containing lists (e.g. Sy [3] Ns ) or dicts ( Ns Sy {3} Ns ) can be opened into a new sheet with with Sy z^Y .
.El
.El
.
.Pp
The following URL schemes are supported:
.Bl -inset -compact -offset xxx
.It Sy http No (requires Sy requests Ns ); can be used as transport for with another filetype
.It Sy postgres No (requires Sy psycopg2 Ns )
.El
.
.Pp
.Bl -inset -compact
.It The following sources may include multiple tables.  The initial sheet is the table directory;
.Sy Enter No loads the entire table into memory.
.El
.
.Pp
.Bl -inset -compact -offset xxx
.It Sy sqlite
.It Sy xlsx No (requires Sy openpyxl Ns )
.It Sy xls No (requires Sy xlrd Ns )
.It Sy hdf5 No (requires Sy h5py Ns )
.It Sy shp No (requires Sy pyshp Ns )
.It Sy mbtiles No (requires Sy mapbox-vector-tile Ns )
.It Sy html No (requires Sy lxml Ns )
.El
.
In addition, .zip and .gz files are decompressed on-the-fly.
.
.Sh AUTHOR
.Nm VisiData
was made by
.An Saul Pwanson Aq Mt vd@saul.pw Ns .
