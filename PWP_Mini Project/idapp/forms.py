from django import forms
from .models import Student, Faculty, Visitor

class StudentForm(forms.ModelForm):
    class Meta:
        model = Student
        exclude = ['valid_through']

    def clean_enrolment_no(self):
        enrolment_no = self.cleaned_data.get('enrolment_no')

        if not enrolment_no.isdigit():
            raise forms.ValidationError("Enrollment number must contain only digits.")

        if len(enrolment_no) != 14:
            raise forms.ValidationError("Enrollment number must be exactly 14 digits long.")

        return enrolment_no


class FacultyForm(forms.ModelForm):
    class Meta:
        model = Faculty
        fields = ['name', 'department', 'faculty_id', 'valid_through', 'photo']
        widgets = {
            'valid_through': forms.DateInput(attrs={'type': 'date'}),
        }


class VisitorForm(forms.ModelForm):
    class Meta:
        model = Visitor
        fields = ['name', 'purpose', 'visit_date', 'photo']
        widgets = {
            'visit_date': forms.DateInput(attrs={'type': 'date'}),
        }
