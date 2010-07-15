function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5477\" class=\"headerLeftMenuInActive\"><a id=\"aID5477\" href=\"#\" OnMouseOver=\"link('_dir','pit0',this)\" class=\"leftMenuLinkHeadInActive\">pit</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5544\" class=\"leftMenuInActive\"><a id=\"aID5544\" href=\"#\" OnMouseOver=\"link('_unit','pit_h0',this)\" class=\"leftMenuLinkInActive\">pit.h</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
