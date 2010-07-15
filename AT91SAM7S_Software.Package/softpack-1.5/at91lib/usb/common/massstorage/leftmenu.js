function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5489\" class=\"headerLeftMenuInActive\"><a id=\"aID5489\" href=\"#\" OnMouseOver=\"link('_dir','massstorage0',this)\" class=\"leftMenuLinkHeadInActive\">massstorage</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Pages</div>\n");
document.write("<div id=\"divID5398\" class=\"leftMenuInActive\"><a id=\"aID5398\" href=\"#\" OnMouseOver=\"link('_page','MSdevicecodes0',this)\" class=\"leftMenuLinkInActive\">MS device codes</a></div>\n");
document.write("<div id=\"divID5399\" class=\"leftMenuInActive\"><a id=\"aID5399\" href=\"#\" OnMouseOver=\"link('_page','MSinterfacecodes0',this)\" class=\"leftMenuLinkInActive\">MS interface codes</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5584\" class=\"leftMenuInActive\"><a id=\"aID5584\" href=\"#\" OnMouseOver=\"link('_unit','MSDeviceDescriptor_h0',this)\" class=\"leftMenuLinkInActive\">MSDeviceDescriptor.h</a></div>\n");
document.write("<div id=\"divID5585\" class=\"leftMenuInActive\"><a id=\"aID5585\" href=\"#\" OnMouseOver=\"link('_unit','MSInterfaceDescriptor_h0',this)\" class=\"leftMenuLinkInActive\">MSInterfaceDescriptor.h</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
