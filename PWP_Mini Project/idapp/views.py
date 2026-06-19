from django.shortcuts import render, get_object_or_404, redirect
from django.http import HttpResponse
from django.template.loader import get_template
from xhtml2pdf import pisa
from django.contrib.auth.decorators import user_passes_test
from .models import Student
from .forms import StudentForm
from datetime import date

# Home page
def home(request):
    return render(request, 'home.html')


# View a single student's ID card
def student_id(request, student_id):
    student = get_object_or_404(Student, id=student_id)
    return render(request, 'student_id.html', {'student': student})


# Generate and download PDF of ID card
def download_id_card_pdf(request, student_id):
    student = get_object_or_404(Student, id=student_id)
    template = get_template('student_id.html')
    context = {'student': student}
    html = template.render(context)

    response = HttpResponse(content_type='application/pdf')
    response['Content-Disposition'] = f'attachment; filename="id_card_{student.id}.pdf"'

    pisa_status = pisa.CreatePDF(html, dest=response)
    if pisa_status.err:
        return HttpResponse('Error generating PDF')

    return response


# Superuser view to list all ID cards
@user_passes_test(lambda u: u.is_superuser)
def all_id_cards(request):
    students = Student.objects.all()
    return render(request, 'all_id_cards.html', {'students': students})


# Handle student creation form
def student_form(request):
    if request.method == 'POST':
        form = StudentForm(request.POST, request.FILES)
        if form.is_valid():
            student = form.save(commit=False)
            student.valid_through = date(2029, 7, 31)  # auto-set
            student.save()
            # Open student_id page in the new tab
            return redirect('student_id', student_id=student.id)
    else:
        form = StudentForm()
    return render(request, 'student_form.html', {'form': form})
