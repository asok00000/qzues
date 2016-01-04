# qzues
An extension lib of Qt<br>
Include styled combobox,line edit with reset function,marquee labe...<br><br>
Any question or advice,please contact me via asok00000@qq.com.<br><br>
Any functiosns those Qt don't provide,can post to my email.I will add it to QZues.<br><br>
Intro<br>
  QZuesLabel<br>
    1.marquee effect like HTML tag Marquee,by set the label type with LABEL_TYPE_MARQUEE and set the step length by setStepLength to control the text move length.<br>
    2.auto fill place holder text when the text length bigger than the label length,set the place holder text via setPlaceholdText the default is "...".<br>
  QZuesComboBox<br>
    1.styled pop-up list,you can set the pop-up list's stype directly via QSS.<br>
  QZuesLineEdit<br>
    1.a line edit with reset function,this line edit will remenber the text which set first,and you can call the reset function to reset the line edit to the original status.And this class will emit text status changed signal.<br>
  QZuesListView<br>
    1.a list view can display tips when the list is empty.call setEmptyTips to set the empty tips.<br>
