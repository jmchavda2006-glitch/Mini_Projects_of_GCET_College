from django.db import models

class Student(models.Model):
    name = models.CharField(max_length=100)
    branch = models.CharField(max_length=100)
    enrolment_no = models.CharField(max_length=50, unique=True)
    valid_through = models.DateField(default='2029-07-31', blank=True, null=True)
    photo = models.ImageField(upload_to='students_photos/')

    def __str__(self):
        return self.name


class Faculty(models.Model):
    name = models.CharField(max_length=100)
    department = models.CharField(max_length=100)
    faculty_id = models.CharField(max_length=50, unique=True)
    valid_through = models.DateField(default='2029-07-31', blank=True, null=True)
    photo = models.ImageField(upload_to='faculty_photos/')

    def __str__(self):
        return self.name


class Visitor(models.Model):
    name = models.CharField(max_length=100)
    purpose = models.CharField(max_length=200)
    visit_date = models.DateField()
    photo = models.ImageField(upload_to='visitor_photos/')

    def __str__(self):
        return self.name
