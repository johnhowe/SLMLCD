function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5491\" class=\"headerLeftMenuInActive\"><a id=\"aID5491\" href=\"#\" OnMouseOver=\"link('_dir','cdcmi_serial0',this)\" class=\"leftMenuLinkHeadInActive\">cdc-serial</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Pages</div>\n");
document.write("<div id=\"divID5404\" class=\"leftMenuInActive\"><a id=\"aID5404\" href=\"#\" OnMouseOver=\"link('_page','CDCSerialDeviceIDs0',this)\" class=\"leftMenuLinkInActive\">CDC Serial Device IDs</a></div>\n");
document.write("<div id=\"divID5405\" class=\"leftMenuInActive\"><a id=\"aID5405\" href=\"#\" OnMouseOver=\"link('_page','CDCSerialEndpoints0',this)\" class=\"leftMenuLinkInActive\">CDC Serial Endpoints</a></div>\n");
document.write("<div id=\"divID5403\" class=\"leftMenuInActive\"><a id=\"aID5403\" href=\"#\" OnMouseOver=\"link('_page','CDCSerialPortStates0',this)\" class=\"leftMenuLinkInActive\">CDC Serial Port States</a></div>\n");
document.write("<div id=\"divID5400\" class=\"leftMenuInActive\"><a id=\"aID5400\" href=\"#\" OnMouseOver=\"link('_page','USBCDCSerialDevice0',this)\" class=\"leftMenuLinkInActive\">USB CDC Serial Device</a></div>\n");
document.write("<div id=\"divID5401\" class=\"leftMenuInActive\"><a id=\"aID5401\" href=\"#\" OnMouseOver=\"link('_page','USBCDCSerialHostDriver0',this)\" class=\"leftMenuLinkInActive\">USB CDC Serial Host Driver</a></div>\n");
document.write("<div id=\"divID5402\" class=\"leftMenuInActive\"><a id=\"aID5402\" href=\"#\" OnMouseOver=\"link('_page','USBDualPortCDCSerialDevice0',this)\" class=\"leftMenuLinkInActive\">USB Dual Port CDC Serial Device</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5588\" class=\"leftMenuInActive\"><a id=\"aID5588\" href=\"#\" OnMouseOver=\"link('_unit','CDCDSerialDriver_h0',this)\" class=\"leftMenuLinkInActive\">CDCDSerialDriver.h</a></div>\n");
document.write("<div id=\"divID5589\" class=\"leftMenuInActive\"><a id=\"aID5589\" href=\"#\" OnMouseOver=\"link('_unit','CDCDSerialDriverDescriptors_h0',this)\" class=\"leftMenuLinkInActive\">CDCDSerialDriverDescriptors.h</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
