function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5496\" class=\"headerLeftMenuInActive\"><a id=\"aID5496\" href=\"#\" OnMouseOver=\"link('_dir','hidmi_keyboard0',this)\" class=\"leftMenuLinkHeadInActive\">hid-keyboard</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Pages</div>\n");
document.write("<div id=\"divID5423\" class=\"leftMenuInActive\"><a id=\"aID5423\" href=\"#\" OnMouseOver=\"link('_page','HIDDeviceDescriptorIDs0',this)\" class=\"leftMenuLinkInActive\">HID Device Descriptor IDs</a></div>\n");
document.write("<div id=\"divID5424\" class=\"leftMenuInActive\"><a id=\"aID5424\" href=\"#\" OnMouseOver=\"link('_page','HIDEndpoints0',this)\" class=\"leftMenuLinkInActive\">HID Endpoints</a></div>\n");
document.write("<div id=\"divID5425\" class=\"leftMenuInActive\"><a id=\"aID5425\" href=\"#\" OnMouseOver=\"link('_page','HIDKeypadkeys0',this)\" class=\"leftMenuLinkInActive\">HID Keypad keys</a></div>\n");
document.write("<div id=\"divID5422\" class=\"leftMenuInActive\"><a id=\"aID5422\" href=\"#\" OnMouseOver=\"link('_page','USBHIDBasic0',this)\" class=\"leftMenuLinkInActive\">USB HID Basic</a></div>\n");
document.write("<div id=\"divID5420\" class=\"leftMenuInActive\"><a id=\"aID5420\" href=\"#\" OnMouseOver=\"link('_page','USBHIDKeyboard0',this)\" class=\"leftMenuLinkInActive\">USB HID Keyboard</a></div>\n");
document.write("<div id=\"divID5421\" class=\"leftMenuInActive\"><a id=\"aID5421\" href=\"#\" OnMouseOver=\"link('_page','USBHIDMouse0',this)\" class=\"leftMenuLinkInActive\">USB HID Mouse</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5598\" class=\"leftMenuInActive\"><a id=\"aID5598\" href=\"#\" OnMouseOver=\"link('_unit','HIDDKeyboardCallbacks_h0',this)\" class=\"leftMenuLinkInActive\">HIDDKeyboardCallbacks.h</a></div>\n");
document.write("<div id=\"divID5599\" class=\"leftMenuInActive\"><a id=\"aID5599\" href=\"#\" OnMouseOver=\"link('_unit','HIDDKeyboardDriver_h0',this)\" class=\"leftMenuLinkInActive\">HIDDKeyboardDriver.h</a></div>\n");
document.write("<div id=\"divID5600\" class=\"leftMenuInActive\"><a id=\"aID5600\" href=\"#\" OnMouseOver=\"link('_unit','HIDDKeyboardDriverDescriptors_h0',this)\" class=\"leftMenuLinkInActive\">HIDDKeyboardDriverDescriptors.h</a></div>\n");
document.write("<div id=\"divID5601\" class=\"leftMenuInActive\"><a id=\"aID5601\" href=\"#\" OnMouseOver=\"link('_unit','HIDDKeyboardInputReport_h0',this)\" class=\"leftMenuLinkInActive\">HIDDKeyboardInputReport.h</a></div>\n");
document.write("<div id=\"divID5602\" class=\"leftMenuInActive\"><a id=\"aID5602\" href=\"#\" OnMouseOver=\"link('_unit','HIDDKeyboardOutputReport_h0',this)\" class=\"leftMenuLinkInActive\">HIDDKeyboardOutputReport.h</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
