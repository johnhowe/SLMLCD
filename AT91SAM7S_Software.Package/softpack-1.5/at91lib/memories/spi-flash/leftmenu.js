function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5468\" class=\"headerLeftMenuInActive\"><a id=\"aID5468\" href=\"#\" OnMouseOver=\"link('_dir','spimi_flash0',this)\" class=\"leftMenuLinkHeadInActive\">spi-flash</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5533\" class=\"leftMenuInActive\"><a id=\"aID5533\" href=\"#\" OnMouseOver=\"link('_unit','at26_h0',this)\" class=\"leftMenuLinkInActive\">at26.h</a></div>\n");
document.write("<div id=\"divID5534\" class=\"leftMenuInActive\"><a id=\"aID5534\" href=\"#\" OnMouseOver=\"link('_unit','at45_h0',this)\" class=\"leftMenuLinkInActive\">at45.h</a></div>\n");
document.write("<div id=\"divID5535\" class=\"leftMenuInActive\"><a id=\"aID5535\" href=\"#\" OnMouseOver=\"link('_unit','spid_h0',this)\" class=\"leftMenuLinkInActive\">spid.h</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
