# coding=utf-8
import click
import dash
import dash_core_components as dcc
import dash_html_components as html
import datetime
import glob
import logging
import os
import plotly.graph_objs as go
import sys
from threading import Lock

from file_reader import load

logger = logging.getLogger()
handler = logging.StreamHandler(sys.stdout)
formatter = logging.Formatter(
    '%(asctime)s %(levelname)-8s %(message)s')
handler.setFormatter(formatter)
logger.addHandler(handler)
logger.setLevel(logging.DEBUG)

# График аргумента комплексного значения часто называют в данном случае “фазовым спектром”, а график модуля —
# “амплитудным спектром”.
graphs = ['amplitude', 'phase', 'log10']

runtime = {}
runtime_lock = Lock()

external_stylesheets = ['https://codepen.io/chriddyp/pen/bWLwgP.css']




def make_centered_p(text):
    return html.P(text, style={'text-align': 'center', 'font-style': 'bold'})


@click.command('run')
@click.argument('dir_path', type=str)
def run(dir_path):
    runtime['dir_path'] = os.path.expanduser(dir_path)

    if not os.path.exists(runtime['dir_path']):
        logger.error('Directory %s does not exist, exiting', runtime['dir_path'])
        return

    logger.debug(glob.glob(os.path.expanduser(runtime['dir_path'] + os.sep + "*.fou")))
    runtime['files'] = list(
        map(os.path.basename, glob.glob(os.path.expanduser(runtime['dir_path'] + os.sep + "*.fou"))))
    if len(runtime['files']) == 0:
        logger.error('List of .fou files is empty, exiting')
        return

    logger.debug(runtime['files'])

    runtime['file'] = None
    with runtime_lock:
        update_file(0)

    app = dash.Dash(__name__, external_stylesheets=external_stylesheets)

    app.layout = html.Div([
        html.H1('PRAO Data Viewer'),
        html.I('That’s one small step for a man, but one giant leap for mankind.'),
        html.Br(),
        html.Br(),

        dcc.Dropdown(
            options=[{'label': runtime['files'][i], 'value': str(i)} for i in range(len(runtime['files']))],
            value=str(runtime['file']),
            id='file-changer'
        ),
        html.Br(),
        html.H4(id='ray-header'),
        html.H4(id='time-header'),

        html.Br(),
        html.H2('signals'),
        dcc.Graph(id='fourier-scatter')

    ], style={'margin-left': '50px', 'margin-right': '50px'})

    @app.callback(
        dash.dependencies.Output('fourier-scatter', 'figure'),
        [dash.dependencies.Input('file-changer', 'value')]
    )
    def update_figure(selected_file):
        logger.debug('enter update_figure_1(%s)', selected_file)
        if int(selected_file) != runtime['file']:
            with runtime_lock:
                update_file(selected_file)
        df = runtime['df']
        traces = []
        traces.append(go.Scatter(
            x=df['channel'],
            y=df['modulus'],
            x0=0,
            y0=0,
            mode='lines+markers',
            marker={
                'size': 3
            },
            name='amplitude'
        ))
        logger.debug('traces' + str(traces))
        return {
            'data': traces,
            'layout': go.Layout(
                xaxis={'range': [0, 10000]},
                yaxis={'range': [0, 2000]},
                margin={'l': 40, 'b': 40, 't': 10, 'r': 10},
                legend={'x': 1, 'y': 1},
                hovermode='closest'
            )
        }

    @app.callback(
        dash.dependencies.Output('ray-header', 'children'),
        [dash.dependencies.Input('file-changer', 'value')]
    )
    def update_ray_header(selected_file):
        if int(selected_file) != runtime['file']:
            with runtime_lock:
                update_file(selected_file)
        header = runtime['header']
        return 'ray: ' + header['ray_number']

    @app.callback(
        dash.dependencies.Output('time-header', 'children'),
        [dash.dependencies.Input('file-changer', 'value')]
    )
    def update_time_header(selected_file):
        if int(selected_file) != runtime['file']:
            with runtime_lock:
                update_file(selected_file)
        header = runtime['header']
        elapsed_time = int(header['utc_begin'])
        return 'utc_begin: ' + datetime.datetime.fromtimestamp(int(elapsed_time)).strftime('%Y-%m-%d %H:%M:%S')


    app.run_server(debug=False)


def update_file(selected_file):
    logging.debug('selected_file = %s, runtime_file = %s', selected_file, runtime['file'])
    if int(selected_file) == runtime['file']:
        return

    runtime['file'] = int(selected_file)
    logger.debug('Loading %s',
                 os.path.expanduser(os.path.join(runtime['dir_path'], runtime['files'][runtime['file']])))
    logger.debug('loading file...')
    df, header = load(os.path.expanduser(os.path.join(runtime['dir_path'], runtime['files'][runtime['file']])))
    runtime['df'] = df
    runtime['header'] = header
    logger.debug('done...')

if __name__ == '__main__':
    run()
