function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5495\" class=\"headerLeftMenuInActive\"><a id=\"aID5495\" href=\"#\" OnMouseOver=\"link('_dir','device0',this)\" class=\"leftMenuLinkHeadInActive\">device</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID5490\" class=\"leftMenuInActive\"><a id=\"aID5490\" href=\"#\" OnMouseOver=\"link('_dir','ccid/ccid0',this)\" class=\"leftMenuLinkInActive\">ccid</a></div>\n");
document.write("<div id=\"divID5491\" class=\"leftMenuInActive\"><a id=\"aID5491\" href=\"#\" OnMouseOver=\"link('_dir','cdc-serial/cdcmi_serial0',this)\" class=\"leftMenuLinkInActive\">cdc-serial</a></div>\n");
document.write("<div id=\"divID5492\" class=\"leftMenuInActive\"><a id=\"aID5492\" href=\"#\" OnMouseOver=\"link('_dir','composite/composite0',this)\" class=\"leftMenuLinkInActive\">composite</a></div>\n");
document.write("<div id=\"divID5494\" class=\"leftMenuInActive\"><a id=\"aID5494\" href=\"#\" OnMouseOver=\"link('_dir','core/core0',this)\" class=\"leftMenuLinkInActive\">core</a></div>\n");
document.write("<div id=\"divID5496\" class=\"leftMenuInActive\"><a id=\"aID5496\" href=\"#\" OnMouseOver=\"link('_dir','hid-keyboard/hidmi_keyboard0',this)\" class=\"leftMenuLinkInActive\">hid-keyboard</a></div>\n");
document.write("<div id=\"divID5497\" class=\"leftMenuInActive\"><a id=\"aID5497\" href=\"#\" OnMouseOver=\"link('_dir','hid-mouse/hidmi_mouse0',this)\" class=\"leftMenuLinkInActive\">hid-mouse</a></div>\n");
document.write("<div id=\"divID5498\" class=\"leftMenuInActive\"><a id=\"aID5498\" href=\"#\" OnMouseOver=\"link('_dir','hid-transfer/hidmi_transfer0',this)\" class=\"leftMenuLinkInActive\">hid-transfer</a></div>\n");
document.write("<div id=\"divID5499\" class=\"leftMenuInActive\"><a id=\"aID5499\" href=\"#\" OnMouseOver=\"link('_dir','massstorage/massstorage0',this)\" class=\"leftMenuLinkInActive\">massstorage</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Pages</div>\n");
document.write("<div id=\"divID5416\" class=\"leftMenuInActive\"><a id=\"aID5416\" href=\"#\" OnMouseOver=\"link('_page','USBDeviceStateDiagram0',this)\" class=\"leftMenuLinkInActive\">USB Device State Diagram</a></div>\n");
document.write("<div id=\"divID5413\" class=\"leftMenuInActive\"><a id=\"aID5413\" href=\"#\" OnMouseOver=\"link('_page','USBDAPI0',this)\" class=\"leftMenuLinkInActive\">USBD API</a></div>\n");
document.write("<div id=\"divID5415\" class=\"leftMenuInActive\"><a id=\"aID5415\" href=\"#\" OnMouseOver=\"link('_page','USBDAPIMethods0',this)\" class=\"leftMenuLinkInActive\">USBD API Methods</a></div>\n");
document.write("<div id=\"divID5414\" class=\"leftMenuInActive\"><a id=\"aID5414\" href=\"#\" OnMouseOver=\"link('_page','USBDAPIStructures0',this)\" class=\"leftMenuLinkInActive\">USBD API Structures</a></div>\n");
document.write("<div id=\"divID5417\" class=\"leftMenuInActive\"><a id=\"aID5417\" href=\"#\" OnMouseOver=\"link('_page','USBDCallbackAPI0',this)\" class=\"leftMenuLinkInActive\">USBD Callback API</a></div>\n");
document.write("<div id=\"divID5418\" class=\"leftMenuInActive\"><a id=\"aID5418\" href=\"#\" OnMouseOver=\"link('_page','USBDStandardRequestHandler0',this)\" class=\"leftMenuLinkInActive\">USBD Standard Request Handler</a></div>\n");
document.write("<div id=\"divID5419\" class=\"leftMenuInActive\"><a id=\"aID5419\" href=\"#\" OnMouseOver=\"link('_page','VIDco_PIDco_SNam_Strings0',this)\" class=\"leftMenuLinkInActive\">VID, PID, SN & Strings</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
