import plotly.graph_objs as go
import pandas as pd
import numpy as np


x = [1, 2, 3,]
y = [1, 2, 7,]

y_upper = [2, 3, 8, ]
y_lower = [1, 2, 5, ]
fig = go.Figure([
    go.Scatter(
        name='Measurement',
        x=x,
        y=y,
        mode='lines',
        line=dict(color='rgb(31, 119, 180)'),
    ),
    go.Scatter(
        name='Upper Bound',
        x=x,
        y=np.array(y)+np.array(y_upper),
        mode='lines',
        marker=dict(color="#444"),
        line=dict(width=0),
        showlegend=False
    ),
    go.Scatter(
        name='Lower Bound',
        x=x,
        y=np.array(y)-np.array(y_lower),
        marker=dict(color="#444"),
        line=dict(width=0),
        mode='lines',
        fillcolor='rgba(68, 68, 68, 0.3)',
        fill='tonexty',
        showlegend=False
    )
])
fig.update_layout(
    yaxis_title='Wind speed (m/s)',
    title='Continuous, variable value error bars',
    hovermode="x"
)
fig.show()
