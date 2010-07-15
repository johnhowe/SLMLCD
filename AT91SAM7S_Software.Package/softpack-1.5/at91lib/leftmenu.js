function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5456\" class=\"headerLeftMenuInActive\"><a id=\"aID5456\" href=\"#\" OnMouseOver=\"link('_dir','at91lib0',this)\" class=\"leftMenuLinkHeadInActive\">at91lib</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID5459\" class=\"leftMenuInActive\"><a id=\"aID5459\" href=\"#\" OnMouseOver=\"link('_dir','boards/boards0',this)\" class=\"leftMenuLinkInActive\">boards</a></div>\n");
document.write("<div id=\"divID5460\" class=\"leftMenuInActive\"><a id=\"aID5460\" href=\"#\" OnMouseOver=\"link('_dir','components/components0',this)\" class=\"leftMenuLinkInActive\">components</a></div>\n");
document.write("<div id=\"divID5463\" class=\"leftMenuInActive\"><a id=\"aID5463\" href=\"#\" OnMouseOver=\"link('_dir','drivers/drivers0',this)\" class=\"leftMenuLinkInActive\">drivers</a></div>\n");
document.write("<div id=\"divID5466\" class=\"leftMenuInActive\"><a id=\"aID5466\" href=\"#\" OnMouseOver=\"link('_dir','memories/memories0',this)\" class=\"leftMenuLinkInActive\">memories</a></div>\n");
document.write("<div id=\"divID5475\" class=\"leftMenuInActive\"><a id=\"aID5475\" href=\"#\" OnMouseOver=\"link('_dir','peripherals/peripherals0',this)\" class=\"leftMenuLinkInActive\">peripherals</a></div>\n");
document.write("<div id=\"divID5500\" class=\"leftMenuInActive\"><a id=\"aID5500\" href=\"#\" OnMouseOver=\"link('_dir','usb/usb0',this)\" class=\"leftMenuLinkInActive\">usb</a></div>\n");
document.write("<div id=\"divID5501\" class=\"leftMenuInActive\"><a id=\"aID5501\" href=\"#\" OnMouseOver=\"link('_dir','utility/utility0',this)\" class=\"leftMenuLinkInActive\">utility</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
