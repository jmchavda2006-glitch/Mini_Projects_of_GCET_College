from django.contrib import admin
from django.utils.html import format_html
from django.urls import reverse
from .models import Student, Faculty, Visitor

class StudentAdmin(admin.ModelAdmin):
    list_display = ('name', 'branch', 'enrolment_no', 'valid_through', 'view_id_card_link')
    
    def view_id_card_link(self, obj):
        url = reverse('student_id', args=[obj.id])
        return format_html('<a href="{}" target="_blank">View ID Card</a>', url)
    
    view_id_card_link.short_description = 'ID Card'

admin.site.register(Student, StudentAdmin)
admin.site.register(Faculty)
admin.site.register(Visitor)
