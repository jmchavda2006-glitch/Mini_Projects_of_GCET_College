from django.urls import path
from . import views

urlpatterns = [
    path('', views.home, name='home'),
    path('student/<int:student_id>/', views.student_id, name='student_id'),
    path('student/<int:student_id>/download/', views.download_id_card_pdf, name='download_id_card_pdf'),
    path('all-id-cards/', views.all_id_cards, name='all_id_cards'),
    path('student-form/', views.student_form, name='student_form'),
]
