
/* There is a version of this file commented in great detail for educational purposes here:
 * http://users.tpg.com.au/j_birch/plugins/superfish/superfish.commented.css
 */

/*** ESSENTIAL STYLES ***/
#editmenu, #editmenu * {
  margin: 0;
  padding: 0;
  list-style: none;
}

#editmenu {
  line-height: 1.0;
  @FIX@
  @MENUBAR_ZINDEX@
}

#editmenu ul {
  position: absolute;
  top: -999em;
  width: 14em;
  font-size: 1em;
  line-height: 1em;
}

#editmenu ul li,
#editmenu a {
  width: 100%;
}

#editmenu li {
  float: left;
  position: relative;
}

#editmenu a {
  display: block;
}

#editmenu li ul {
  @DROPDOWN_ZINDEX@
}

#editmenu li:hover ul,
ul#editmenu li.sfHover ul {
  left: 0px;
  top: 21px;
}

#editmenu li:hover li ul,
#editmenu li.sfHover li ul {
  top: -999em;
}

#editmenu li li:hover ul,
ul#editmenu li li.sfHover ul {
  left: 14em;
  top: -1px;
}

.superfish li:hover ul,
.superfish li li:hover ul {
  top: -999em;
}

/* vim: ts=2 sw=2 et syntax=css
*/
