function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5498\" class=\"headerLeftMenuInActive\"><a id=\"aID5498\" href=\"#\" OnMouseOver=\"link('_dir','hidmi_transfer0',this)\" class=\"leftMenuLinkHeadInActive\">hid-transfer</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Pages</div>\n");
document.write("<div id=\"divID5429\" class=\"leftMenuInActive\"><a id=\"aID5429\" href=\"#\" OnMouseOver=\"link('_page','HIDTransferDeviceDescriptorIDs0',this)\" class=\"leftMenuLinkInActive\">HID Transfer Device Descriptor IDs</a></div>\n");
document.write("<div id=\"divID5428\" class=\"leftMenuInActive\"><a id=\"aID5428\" href=\"#\" OnMouseOver=\"link('_page','USBHIDTransfer0',this)\" class=\"leftMenuLinkInActive\">USB HID Transfer</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5606\" class=\"leftMenuInActive\"><a id=\"aID5606\" href=\"#\" OnMouseOver=\"link('_unit','HIDDTransferDriver_h0',this)\" class=\"leftMenuLinkInActive\">HIDDTransferDriver.h</a></div>\n");
document.write("<div id=\"divID5607\" class=\"leftMenuInActive\"><a id=\"aID5607\" href=\"#\" OnMouseOver=\"link('_unit','HIDDTransferDriverDesc_h0',this)\" class=\"leftMenuLinkInActive\">HIDDTransferDriverDesc.h</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
