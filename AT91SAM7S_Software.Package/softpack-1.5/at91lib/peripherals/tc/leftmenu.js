function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5482\" class=\"headerLeftMenuInActive\"><a id=\"aID5482\" href=\"#\" OnMouseOver=\"link('_dir','tc0',this)\" class=\"leftMenuLinkHeadInActive\">tc</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5547\" class=\"leftMenuInActive\"><a id=\"aID5547\" href=\"#\" OnMouseOver=\"link('_unit','tc_h0',this)\" class=\"leftMenuLinkInActive\">tc.h</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
