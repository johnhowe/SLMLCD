function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5472\" class=\"headerLeftMenuInActive\"><a id=\"aID5472\" href=\"#\" OnMouseOver=\"link('_dir','dbgu0',this)\" class=\"leftMenuLinkHeadInActive\">dbgu</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5539\" class=\"leftMenuInActive\"><a id=\"aID5539\" href=\"#\" OnMouseOver=\"link('_unit','dbgu_h0',this)\" class=\"leftMenuLinkInActive\">dbgu.h</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
