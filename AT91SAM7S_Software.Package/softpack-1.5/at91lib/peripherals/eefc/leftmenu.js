function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5473\" class=\"headerLeftMenuInActive\"><a id=\"aID5473\" href=\"#\" OnMouseOver=\"link('_dir','eefc0',this)\" class=\"leftMenuLinkHeadInActive\">eefc</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5540\" class=\"leftMenuInActive\"><a id=\"aID5540\" href=\"#\" OnMouseOver=\"link('_unit','eefc_h0',this)\" class=\"leftMenuLinkInActive\">eefc.h</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
