function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5502\" class=\"headerLeftMenuInActive\"><a id=\"aID5502\" href=\"#\" OnMouseOver=\"link('_dir','basicmi_adcmi_project0',this)\" class=\"leftMenuLinkHeadInActive\">basic-adc-project</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
