from bs4 import BeautifulSoup
import requests
import time

print('Put some skills that you are not familiar with')
unfamiliar_skill = input('>')
print(f'Filtering out {unfamiliar_skill}')

def find_job():
    html_text = requests.get('').text
    soup = BeautifulSoup(html_text, 'lxml')
    jobs = soup.find_all('li', class_='')
    for job in enumerate(jobs):
        publised_date = job.find('', class_='').span.text.replace(' ', '')
        if 'few' in publised_date:
            company_name = job.find('h3', class_='').text.replace(' ','')
            skills = job.find('', class_='').text.replace(' ', '')
            more_info = job.header,h2.a.'href']
            if unfamiliar_skill not in skills:

                with open(f'posts/{index}.txt, 'w') as f:
                    f.write(f'Company Name:{company_name.strip()}\n')
                    f.write(f'Required Skills: {skills.strip()}\n')
                    f.write(f'More Info: {more_info}') 
                print(f'File saved: {index}')

if __name__ == '__main__':
    while True:
        find_job()
        time_wait = 10
        print(f'Waiting {time_wait} minutes...')
        time.sleep(time_wait*60)
                    
