NDSummary.OnToolTipsLoaded("File:SDFileHandler.h",{13:"<div class=\"NDToolTip TInformation LC\"><div class=\"TTSummary\">The standard SD File handling code is <u>borked</u> on Arduino.&nbsp; This is an effort to get around that problem - these problems actually!</div></div>",5:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">SDFileHandler(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\"><span class=\"SHKeyword\">char</span>&nbsp;</td><td class=\"PNamePrefix\">*</td><td class=\"PName\">fileName,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"first\"></td><td class=\"PType\">uint8_t&nbsp;</td><td></td><td class=\"PName\">openMode&nbsp;</td><td class=\"PDefaultValueSeparator\">=&nbsp;</td><td class=\"PDefaultValue last\">FILE_READ</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">The constructor assumes that the SD Card system has already been initialised and that no files are open.</div></div>",2:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">SDFileHandler(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\">String&nbsp;</td><td class=\"PName\">fileName,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"PType first\">uint8_t&nbsp;</td><td class=\"PName\">openMode&nbsp;</td><td class=\"PDefaultValueSeparator\">=&nbsp;</td><td class=\"PDefaultValue last\">FILE_READ</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">This constructor takes the same parameters as above, but the filename is an Arduino String in this case.</div></div>",7:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype7\" class=\"NDPrototype NoParameterForm\">~SDFileHandler()</div><div class=\"TTSummary\">Closes down any opened files before the object goes out of scope.</div></div>",10:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype10\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> reOpen(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\">uint8_t&nbsp;</td><td class=\"PName last\">openMode</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Given an open file, close it, then reopen it in the specified mode.</div></div>",11:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype11\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">void</span> close()</div><div class=\"TTSummary\">Close a file. There are no parameters as the file handle held in theFile will be closed.</div></div>",4:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4\" class=\"NDPrototype NoParameterForm\">File getHandle()</div><div class=\"TTSummary\">Return a handle to the underlying File which is stored internally in theFile. The returned handle can be used to call underlying File functions such as <b>position</b> and <b>seek</b> etc.</div></div>",14:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype14\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">size_t write(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">byte</span>&nbsp;</td><td class=\"PName last\">data</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Various write functions to correct the borked stuff in the Arduino File implementation. The write function is overloaded to allow the following data types to be written to a file:</div></div>",15:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype15\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">size_t SDFileHandler::writeData(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\">uint8_t&nbsp;</td><td class=\"PNamePrefix\">*</td><td class=\"PName last\">data,</td></tr><tr><td class=\"PType first\">uint32_t&nbsp;</td><td></td><td class=\"PName last\">dataLength</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Write arbitrary data to the SD Card file. The data written is preceeded by a long (4 bytes) word containing the size of the following data. There is no terminator byte.</div></div>",16:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype16\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">byte</span> readByte()</div><div class=\"TTSummary\">Returns one byte from the SD Card file.</div></div>",17:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype17\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">short</span> readShort()</div><div class=\"TTSummary\">Returns a pair of bytes, into a short variable, from the SD Card file.</div></div>",18:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype18\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">int</span> readInt()</div><div class=\"TTSummary\">Returns a pair of bytes, into an int variable, from the SD Card file.</div></div>",19:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype19\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">long</span> readLong()</div><div class=\"TTSummary\">Returns 4 bytes, into a long variable, from the SD Card file.</div></div>",20:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype20\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> readFloat()</div><div class=\"TTSummary\">Returns 4 bytes, into a float variable, from the SD Card file.</div></div>",21:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype21\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">uint32_t readData(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\">uint8_t&nbsp;</td><td class=\"PNamePrefix\">*</td><td class=\"PName last\">buffer,</td></tr><tr><td class=\"PType first\">uint32_t&nbsp;</td><td></td><td class=\"PName last\">bufferLength</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Returns a number of bytes, into an existing buffer, from the SD Card file.</div></div>",8:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype8\" class=\"NDPrototype NoParameterForm\">File theFile</div><div class=\"TTSummary\">This <b>private</b> variable holds onto the underlying File handle. It is used internally and cannot be accessed except by calling getHandle.</div></div>",9:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype9\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">char</span> *theFileName</div><div class=\"TTSummary\">This <b>private</b> variable holds the filename that the file was originally opened with. It will be in 8.3 format. It is only held for use by the reOpen function, so that a file can, if necessary, be opened for writing then re-opened for reading immediately afterwards.</div></div>"});