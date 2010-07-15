function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5464\" class=\"headerLeftMenuInActive\"><a id=\"aID5464\" href=\"#\" OnMouseOver=\"link('_dir','twi0',this)\" class=\"leftMenuLinkHeadInActive\">twi</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
