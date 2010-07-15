function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5465\" class=\"headerLeftMenuInActive\"><a id=\"aID5465\" href=\"#\" OnMouseOver=\"link('_dir','flash0',this)\" class=\"leftMenuLinkHeadInActive\">flash</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5530\" class=\"leftMenuInActive\"><a id=\"aID5530\" href=\"#\" OnMouseOver=\"link('_unit','flashd_h0',this)\" class=\"leftMenuLinkInActive\">flashd.h</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
