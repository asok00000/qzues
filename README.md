# qzues
An extension lib of Qt 5.x<br>
Include styled combobox,line edit with reset function,marquee labe...<br><br>
Any question or advice,please contact me via asok00000@qq.com.<br><br>
Any functiosns those Qt don't provide,can post to my email.I will add it to QZues.<br><br>
<b>Intro</b><br>
   <b>QZuesLabel</b><br>
    1.marquee effect like HTML tag Marquee,by set the label type with <code>LABEL_TYPE_MARQUEE</code> and set the step length by <code>setStepLength</code> to control the text move length.<br>
    2.auto fill place holder text when the text length bigger than the label length,set the place holder text via <code>setPlaceholdText</code> the default is "...".<br>
  <b>QZuesComboBox</b><br>
    1.styled pop-up list,you can set the pop-up list's stype directly via QSS.<br>
  <b>QZuesLineEdit</b><br>
    1.a line edit with reset function,this line edit will remenber the text which set first,and you can call the <code>reset</code> function to reset the line edit to the original status.And this class will emit text status changed signal.<br>
  <b>QZuesListView</b><br>
    1.a list view can display tips when the list is empty.call <code>setEmptyTips</code> to set the empty tips.<br>
  <b>QZuesCircle</b><br>
    1.a circle progress bar,you can call <code>setTextVisible</code> to show or hide the text percent,call <code>setActiveColor</code> and <code>setDeactiveColor</code> to set the circle color or text color<br>
