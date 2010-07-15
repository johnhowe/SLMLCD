function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5522\" class=\"headerLeftMenuInActive\"><a id=\"aID5522\" href=\"#\" OnMouseOver=\"link('_dir','HIDTest0',this)\" class=\"leftMenuLinkHeadInActive\">HIDTest</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
